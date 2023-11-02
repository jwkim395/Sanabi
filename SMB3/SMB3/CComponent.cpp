#include "pch.h"
#include "CComponent.h"

#include "CObj.h"

CComponent::CComponent(CObj* _Owner)
	: m_pOwner(_Owner)
{
}

CComponent::~CComponent()
{
}
