#include <cstdlib>
#include <fstream>
#include <limits.h>

#include "../state/state.hpp"
#include "./random.hpp"
// std::ofstream fout("randomPol.txt", std::ios::app);

static std::string y_axis = "654321";
static std::string x_axis = "ABCDE";


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

//Minimax code

int Random::minimax(State *node, int depth, bool maximizingPlayer, int alpha, int beta){

  if(depth==0 || node->game_state==WIN||node->game_state==DRAW){
      return node->evaluate();
  }
  if(maximizingPlayer){
        int value = INT_MIN;
        node->get_legal_actions();
        auto actions = node->legal_actions;
        for(auto i = actions.begin();i!=actions.end();i++){
          auto child = node->next_state(*i);
          value = std::max(value, minimax(child, depth-1, false, alpha,beta));
          alpha = std::max(alpha,value);
          if(alpha>=beta){
            break;
      }
  }
      return value;
  }
  else{
    int value = INT_MAX;
    node->get_legal_actions();
    auto actions = node->legal_actions;
    for(auto i = actions.begin();i!=actions.end();i++){
          auto child = node->next_state(*i);
          value = std::min(value, minimax(child, depth-1, true, alpha,beta));
          beta = std::min(beta,value);
          if(beta<=alpha){
            break;
          }
    }
    return value;
  }
}



Move Random::get_move(State *state, int depth){
  if(!state->player){
      int bestValue = INT_MIN;
      Move idealMove (Point(-1,-1),Point(-1,-1));
      state->get_legal_actions();
      auto actionsList = state->legal_actions;
      for(auto i = actionsList.begin();i!=actionsList.end();i++){
          State *temp = state->next_state(*i);
          int value = minimax(temp, depth-1, false, INT_MIN,INT_MAX);
          if(value>bestValue){
            bestValue=value;
            idealMove = *i;
          }
      }
      return idealMove; 
  }
  else{
      int bestValue = INT_MAX;
      Move idealMove (Point(-1,-1),Point(-1,-1));
      state->get_legal_actions();
      auto actionsList = state->legal_actions;
      for(auto i = actionsList.begin();i!=actionsList.end();i++){
          State *temp = state->next_state(*i);
          int value = minimax(temp, depth-1, true, INT_MIN,INT_MAX);
          if(value<bestValue){
            bestValue=value;
            idealMove = *i;
          }
      }
      return idealMove;
  }
}
