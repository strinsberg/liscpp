#ifndef LISCPP_LIST_H
#define LISCPP_LIST_H

#include "rep.h"
#include "type.h"
#include "value.h"

namespace liscpp {

class List : Rep {
public:
  List();
  List(Value, List *);

  inline Value get_data() { return m_data; }
  inline List *get_next() { return m_next; }

  bool operator==(const List &other) const;

  void code_rep(std::ostream &os) const override;
  void display_rep(std::ostream &os) const override;

private:
  Value m_data;
  List *m_next;
};

} // namespace liscpp

#endif
