#include "list.h"
#include <iostream>

using namespace liscpp;

List::List() : m_data{Value()}, m_next{nullptr} {}
List::List(Value data, List *next = nullptr) : m_data{data}, m_next{next} {}

bool List::operator==(const List &other) const {
  // TODO this might work as a recursive deep equality, but it would probably
  // be more efficient to write a loop and move through next pointers.
  return m_data == other.m_data && m_next == other.m_next;
}

bool List::operator<(const List &other) const {
  // TODO again make this iterative
  return m_data < other.m_data && m_next < other.m_next;
}

void List::code_rep(std::ostream &os) const {
  os << "(";
  const List *list = this;
  while (true) {
    list->m_data.code_rep(os);
    if (list->m_next != nullptr) {
      os << " ";
      list = list->m_next;
    } else {
      break;
    }
  }
  os << ")";
}

void List::display_rep(std::ostream &os) const {
  os << "(";
  const List *list = this;
  while (true) {
    list->m_data.display_rep(os);
    if (list->m_next != nullptr) {
      os << " ";
      list = list->m_next;
    } else {
      break;
    }
  }
  os << ")";
}
