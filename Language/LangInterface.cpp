#include "LangInterface.hpp"

NodeInterface::NodeInterface (NodeType type):
    type_ (type)
    {}

ScopeNodeInterface::ScopeNodeInterface (ScopeNodeInterface* previous, ScopeNodeInterface* next):
    NodeInterface (NodeType::SCOPE),
    previous_ (previous),
    next_ (next)
    {}