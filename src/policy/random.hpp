
#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Random{
public:
  static Move get_move(State *state, int depth);
  static int minimax(State *node, int depth, bool maximizingPlayer,int alpha, int beta);
  // int minimax(State* child, int depth , bool maximizingPlayer)
};