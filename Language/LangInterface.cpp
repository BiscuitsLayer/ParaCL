#include "LangInterface.hpp"

NodeInterface::NodeInterface (NodeType type):
    type_ (type)
    {}

ScopeNodeInterface::ScopeNodeInterface (ScopeNodeInterface* previous):
    NodeInterface (NodeType::SCOPE),
    previous_ (previous)
    {}