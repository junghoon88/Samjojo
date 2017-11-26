#include "stdafx.h"
#include "sceneBuy.h"


sceneBuy::sceneBuy()
{

}


sceneBuy::~sceneBuy()
{
}

HRESULT sceneBuy::init(void)
{
	DATABASE->getSlectScenario();


	return S_OK;
}
void sceneBuy::release(void)
{

}
void sceneBuy::update(void)	 
{

}
void sceneBuy::render(void)	 
{

}