#include "stdafx.h"
#include "sceneSell.h"


sceneSell::sceneSell()
{
}


sceneSell::~sceneSell()
{
}


HRESULT sceneSell::init(void) 
{
	DATABASE->getSlectScenario();


	return S_OK;
}
void sceneSell::release(void) 
{

}
void sceneSell::update(void)
{

}
void sceneSell::render(void)
{

}