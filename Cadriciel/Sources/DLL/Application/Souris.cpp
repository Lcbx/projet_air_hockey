///////////////////////////////////////////////////////////////////////////////
/// @file Souris.cpp
/// @author Luc Courbariaux
/// @date 2016-09-12
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "Souris.h"


Selection::Selection() {};

Selection* Selection::instance_{ nullptr };

Selection* Selection::obtenirInstance() {
	if (instance_ == nullptr) instance_ = new Selection;
	return instance_;
}

void Selection::libererInstance() {
	delete instance_;
	instance_ = nullptr;
}

void Selection::startClick(int x, int y) {
	X_ = x; Y_ = y;
}

void Selection::currentClick(int x, int y) {
	X_ = x; Y_ = y;
}

void Selection::endClick(int x, int y) {
	X_ = x; Y_ = y;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////