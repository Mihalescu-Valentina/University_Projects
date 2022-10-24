#include "Player.h"

Player::Player(const string& name, const string& nationality, const string& team, int goals): name{name},nationality{nationality},team{team},goals{goals}
{
}

Player::Player() : name{ "" }, nationality{ "" }, team{ "" },goals{0}
{

}
