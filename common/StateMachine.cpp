//------------------------------------------------------------------------
// StateMachine
//
// Created:	2013/02/10
// Author:	Carel Boers
//	
// State machine that manages state transitions.
//------------------------------------------------------------------------

#include "StateBase.h"
#include "StateMachine.h"
#include "assert.h"

using namespace Common;

//------------------------------------------------------------------------------
// Method:    StateMachine
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
StateMachine::StateMachine()
	:
	m_iCurrentState(-1),
	m_fCurrentStateTime(0.0f),
	m_pOwner(NULL)
{
}

//------------------------------------------------------------------------------
// Method:    ~StateMachine
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
StateMachine::~StateMachine()
{
	for(auto it = m_mStateMap.begin(); it != m_mStateMap.end();it++)
	{
		delete it->second;
	}

	while(m_sStateStack.size() > 0)
	{
		m_sStateStack.pop();
	}
}

//------------------------------------------------------------------------------
// Method:    RegisterState
// Parameter: int p_iState
// Parameter: StateBase * p_pstate
// Returns:   void
// 
// Register a given state with the state manager
//------------------------------------------------------------------------------
void StateMachine::RegisterState(int p_iState, StateBase* p_pstate)
{
	p_pstate->SetStateMachineMembership(this);
	m_mStateMap.insert(std::make_pair<int, StateBase*>(p_iState, p_pstate));
}

//------------------------------------------------------------------------------
// Method:    GoToState
// Parameter: int p_iState
// Returns:   void
// 
// Go to the given state. Make it the active state.
//------------------------------------------------------------------------------
void StateMachine::GoToState(int p_iState)
{
	// Prevent double entering current state
	if (p_iState == m_iCurrentState)
	{
		return;
	}

	StateBase* pState = NULL;
	StateMap::iterator it = m_mStateMap.find(p_iState);
	if (it != m_mStateMap.end())
	{
		pState = static_cast<StateBase*>(it->second);
	}
	assert(pState);

	if(m_sStateStack.size() > 0)
	{
		if(m_sStateStack.top())
		{
			m_sStateStack.top()->Exit();
			m_sStateStack.pop();
		}
	}

	// Set the new current state.
	m_iCurrentState = p_iState;
	m_sStateStack.push(pState);
	m_fCurrentStateTime = 0.0f;

	// Call enter on the new state
	pState->Enter();
}

//------------------------------------------------------------------------------
// Method:    PushState
// Parameter: int p_iState
// Returns:   void
// 
// Push the given state onto our state stack.
//------------------------------------------------------------------------------
void StateMachine::PushState(int p_iState)
{
	StateBase * pState = NULL;
	StateMap::iterator it = m_mStateMap.find(p_iState);
	if(it != m_mStateMap.end())
		pState = static_cast<StateBase*>(it->second);

	assert(pState);

	if(m_sStateStack.size() != 0)
		m_sStateStack.top()->Suspend();

	m_iCurrentState = p_iState;
	m_sStateStack.push(pState);
	m_sStateStack.top()->Enter();
}

//------------------------------------------------------------------------------
// Method:    PopState
// Returns:   void
// 
// Pop the top state from our state stack.
//------------------------------------------------------------------------------
void StateMachine::PopState()
{
	if(!m_sStateStack.empty())
	{
		m_sStateStack.top()->Exit();
		m_sStateStack.pop();
		
		if(!m_sStateStack.empty())
			m_sStateStack.top()->Resume();
	}
}

//------------------------------------------------------------------------------
// Method:    Update
// Parameter: float p_fDelta
// Returns:   void
// 
// Updates the currently active state
//------------------------------------------------------------------------------
void StateMachine::Update(float p_fDelta)
{
	m_fCurrentStateTime += p_fDelta;
	if (m_sStateStack.size() != 0)
		m_sStateStack.top()->Update(p_fDelta);
}