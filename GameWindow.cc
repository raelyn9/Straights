#include "GameWindow.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
using namespace std;

GameWindow::GameWindow(BaseObjectType *cobject, Glib::RefPtr<Gtk::Builder> & builder) : 
						Gtk::Window{cobject}, builder_{builder} {
	
	set_title("Straights");
    set_default_size(600, 600);
	set_border_width(10);

    deckView = make_shared<DeckView>();
    tableView = make_shared<TableView>(deckView);
    hand = make_shared<PlayerHandPanel>(deckView);

    buildHeader(builder_);
    tableView->buildTable(builder_);
    hand->buildPanel(builder_);

    for (size_t i=0; i < 4; ++i) {
        playerPanels.emplace_back(make_shared<PlayerPanel>(i, builder_));
    }

    setDialog();
}

GameWindow::~GameWindow() {
    gameState->detach(this);
    delete inputDialog;
    delete startButton;
    delete endButton;
    delete seedText;
    exit(0);
}


void GameWindow::setController(std::shared_ptr<StraightsController>& inputController) {
    controller = inputController;

    tableView->setTable(controller->getTable());
    hand->setHand( controller->getGameState(), controller);
    setHeader(controller);

    inputDialog->setController(controller);
    inputDialog->set_default_response(Gtk::RESPONSE_YES);
    inputDialog->run();

    for (size_t i=0; i < 4; ++i) {
        playerPanels[i]->setPanel(controller, controller->getGameState());
    }
}

void GameWindow::setGame(){
    gameState = controller->getGameState();
    gameState->attach(this);
    controller->newRound();
}

void GameWindow::setDialog(){
    auto dialogBuilder = Gtk::Builder::create_from_file( "inputDialog.glade" );
    dialogBuilder->get_widget_derived( "inputDialog", inputDialog);
}


void GameWindow::notify() {
    State state = gameState->getState();

    if(state.showHistory) {
        showMesageDialog(gameState->getRecord());
        gameState->setShowHistory(false);
        return;
    }

    if(!state.isLegalPlay) { // output dialog to indicate that the play made is not legal
        showMesageDialog("This is not a legal play.");
        return;
    }

    if (state.roundDone) {
        // output the scores and discards on a dialoge
        vector<int> score = gameState->getScores();
        string resultMsg = "Round end. The results are:\n";
        for (size_t i = 0; i<score.size();i++){

            string discard = playerPanels[i]->getDiscards();
            resultMsg += "Player " + to_string(i+1)+"'s discards : "+ discard + "\n";
            resultMsg += "Player " + to_string(i+1)+"'s scores : "+to_string(score[i])+"\n";
        }
        showMesageDialog(resultMsg);

        if (state.gameDone) {
            // Output the winner(s) on a dialoge
            vector<int> winner = gameState->getWinner();
            string msg = "Game end. The winner is:";
            for (size_t i = 0; i<winner.size();i++){
                msg += " Player " + to_string(winner[i]);
            }
            showMesageDialog(msg);
        } else {
            // output dialog showing that the round is over
            showMesageDialog("Round end. Start the next game.");
            controller->newRound();
        }
    }
}

void GameWindow::showMesageDialog(string str) {
    Gtk::MessageDialog dialog(*this, "Message");
    dialog.set_secondary_text(str);
    dialog.run();
}


void GameWindow::setHeader(std::shared_ptr<StraightsController> inputController){
    controller = inputController;
}

void GameWindow::startButtonClicked() { // player starts game

    // set players
    inputDialog->run();

    // set seed
    string seed = seedText->get_buffer()->get_text();
    istringstream buffer(seed);
    int val;
    buffer >> val;
    controller->setSeed(val);
    controller->startGame();
}

void GameWindow::endButtonClicked() {
    controller->quitGame();
} 

void GameWindow::buildHeader(Glib::RefPtr<Gtk::Builder> & builder_) {
	builder_->get_widget("startGame", startButton);
	builder_->get_widget("endGame", endButton);
	builder_->get_widget("seedText", seedText);

    if ( startButton == nullptr || endButton == nullptr || seedText == nullptr) {
		g_warning("unable to extract window sub-components"); 
		return;
    }

    startButton->signal_clicked().connect(sigc::mem_fun(*this, &GameWindow::startButtonClicked));
	endButton->signal_clicked().connect(sigc::mem_fun(*this, &GameWindow::endButtonClicked));
}
