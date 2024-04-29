#include "list.h"
#include <iostream>

using namespace liscpp;

List::List() : m_data{Value()}, m_next{nullptr} {}
List::List(Value data, List *next = nullptr) : m_data{data}, m_next{next} {}

bool List::operator==(const List &other) const { return false; }

void List::code_rep(std::ostream &os) const { os << "( *UNIMPLEMENTED* )"; }
void List::display_rep(std::ostream &os) const { os << "( *UNIMPLEMENTED* )"; }
