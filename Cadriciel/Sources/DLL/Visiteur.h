#pragma once
#ifndef VISITEUR_H
#define VISITEUR_H

#include <iostream>
#include <string>
#include <NoeudAbstrait.h>
#include <NoeudComposite.h>
/*INCLURE LES AUTRES NOUEDS !!*/

using namespace std;


class Visiteur
{
public:


	virtual void visiter(NoeudAbstrait* noeud) = 0;
	virtual void visiter(NoeudComposite *noeud) = 0;

};
#endif