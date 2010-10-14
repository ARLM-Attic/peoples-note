/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 * Contains some contributions under the Thrift Software License.
 * Please see doc/old-thrift-license.txt in the Thrift distribution for
 * details.
 */

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <stdlib.h>
#include <sys/stat.h>
#include <sstream>

#include "platform.h"
#include "t_oop_generator.h"

using namespace std;

/**
 * Indentation helper.
 */

class t_indent {
private:
  int level;

public:
  t_indent() : level(0) {}
  void up()   { ++level; }
  void down() { --level; }
  void scope_up   (std::ofstream& out_h) { (*this)(out_h) << '{' << std::endl; up(); }
  void scope_down (std::ofstream& out_h) { down(); (*this)(out_h) << '}' << std::endl; }
  std::ofstream& operator () (std::ofstream &out_h) {
    for (int i(0); i != level; ++i)
      out_h << '\t';
    return out_h;
  }
};

/**
 * Windows C++ code generator.
 */
class t_cppw_generator : public t_oop_generator {
public:

  t_cppw_generator(
      t_program* program,
      const map<string, string>& parsed_options,
      const string& option_string);

  /**
   * Init and close methods.
   */

  void init_generator();
  void close_generator();

  /**
   * Program-level entity generators.
   */

  void generate_consts   (vector<t_const*> consts);
  void generate_typedef  (t_typedef  *ttypedef);
  void generate_enum     (t_enum     *tenum);
  void generate_struct   (t_struct   *tstruct);
  void generate_xception (t_struct   *txception);
  void generate_service  (t_service  *tservice);

private:

  /**
   * Const value generation helpers.
   */

  void print_const_value (ofstream& out_h, t_indent& indent_h, string name, t_type* type, t_const_value* value);
  void print_const_constructor (ofstream& out_h, t_indent& indent_h, vector<t_const*> consts);
  void print_const_def_value (ofstream& out_h, t_indent& indent_h, string name, t_type* type, t_const_value* value);

  /**
   * Struct generation helpers.
   */

  void generate_cppw_struct (t_struct* tstruct, bool is_exception);
  void generate_cppw_struct_definition (ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, bool is_xception=false, t_type* parent=NULL, bool is_result=false);
  void generate_cppw_struct_reader (ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, t_type* parent);
  void generate_cppw_struct_result_writer (ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, t_type* parent);
  void generate_cppw_struct_writer (ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, t_type* parent);

  /**
   * Service generation helpers.
   */

  void generate_function_helpers (ofstream & out_h, t_indent& indent, ofstream& out_cpp, t_indent& indent_cpp, t_type* parent, t_function* tfunction);
  void generate_service_interface (ofstream& out_h, t_indent& indent, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice);
  void generate_service_helpers (ofstream& out_h, t_indent& indent, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice);
  void generate_service_client (ofstream& out_h, t_indent& indent, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice);
  void generate_service_server (ofstream& out_h, t_indent& indent, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice);
  void generate_process_function (ofstream& out_h, t_indent& indent, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice, t_function* function);

  /**
   * Serialization helpers.
   */

  void generate_deserialize_field (ofstream& out_h, t_indent& indent_h, t_field* tfield, string prefix="");
  void generate_deserialize_struct (ofstream& out_h, t_indent& indent_h, t_struct* tstruct, string prefix="");
  void generate_deserialize_container (ofstream& out_h, t_indent& indent_h, t_type* ttype, string prefix="");
  void generate_deserialize_set_element (ofstream& out_h, t_indent& indent_h, t_set* tset, string prefix="");
  void generate_deserialize_map_element (ofstream& out_h, t_indent& indent_h, t_map* tmap, string prefix="");
  void generate_deserialize_list_element (ofstream& out_h, t_indent& indent_h, t_list* list, string prefix="");
  void generate_serialize_field (ofstream& out_h, t_indent& indent_h, t_field* tfield, string prefix="");
  void generate_serialize_struct (ofstream& out_h, t_indent& indent_h, t_struct* tstruct, string prefix="");
  void generate_serialize_container (ofstream& out_h, t_indent& indent_h, t_type* ttype, string prefix="");
  void generate_serialize_map_element (ofstream& out_h, t_indent& indent_h, t_map* tmap, string iter, string map);
  void generate_serialize_set_element (ofstream& out_h, t_indent& indent_h, t_set* tmap, string iter);
  void generate_serialize_list_element (ofstream& out_h, t_indent& indent_h, t_list* tlist, string iter);

  /**
   * File creation helpers.
   */

  void start_cppw_namespace (ofstream& out_h);
  void end_cppw_namespace (ofstream& out_h);
  void cppw_header_includes (ofstream& out_h);
  void create_header (string name, ofstream& out_h);
  void create_implementation (string name, ofstream& out_h);
  void using_namespace (ofstream& out_cpp);

  /**
   * Rendering helpers.
   */

  string render_const_value (ofstream& out_h, t_indent& indent_h, string name, t_type* type, t_const_value* value);
  string type_name (t_type* ttype, bool in_typedef=false, bool arg=false);
  string base_type_name (t_type* type);
  string declare_field (t_field* tfield, bool init=false);
  string function_signature (t_function* tfunction, string parent="");
  string argument_list (t_struct* tstruct);
  string type_to_enum (t_type* ttype);
  string namespace_prefix (const vector<string> & ns);
  string unique_name (string name);

  /**
   * Miscellaneous helpers.
   */

  static bool is_complex_type (t_type* ttype);
  static void parse_namespace (const string& ns, vector<string>& result);

private:

  /**
   * Data.
   */

  vector<string> namespaces_;
  string         namespace_dir_;
  ofstream       f_group_;
};

/**
 * Generator implementation.
 */

t_cppw_generator::t_cppw_generator(
    t_program* program,
    const map<string, string>& parsed_options,
    const string& option_string)
  : t_oop_generator(program) {
  out_dir_base_ = "gen-cppw";
}

void t_cppw_generator::init_generator() {
  parse_namespace(program_->get_namespace("cppw"), namespaces_);

  // build the directory tree
  namespace_dir_ = get_out_dir();
  MKDIR(namespace_dir_.c_str());
  for (size_t i = 0; i != namespaces_.size(); ++i)
  {
    namespace_dir_.append("/");
    namespace_dir_.append(namespaces_.at(i));
    MKDIR(namespace_dir_.c_str());
  }

  // create a group header for easy inclusion
  string group_path = namespace_dir_ + "/../" + namespaces_.back() + ".h";
  f_group_.open(group_path.c_str());
}

void t_cppw_generator::start_cppw_namespace(ofstream& out_h) {
  const size_t size = namespaces_.size();
  for (size_t i = 0; i != size; ++i)
  {
    out_h << "namespace " << namespaces_.at(i) << endl;
    out_h << "{" << endl;
  }
}

void t_cppw_generator::end_cppw_namespace(ofstream& out_h) {
  const size_t size = namespaces_.size();
  for (size_t i = 0; i != size; ++i)
    out_h << "} // " << namespaces_.at(size - 1 - i) << endl;
}

void t_cppw_generator::cppw_header_includes(ofstream& out_h) {
  // standard headers
  out_h << "#include <fstream>" << endl;
  out_h << "#include <map>" << endl;
  out_h << "#include <set>" << endl;
  out_h << "#include <string>" << endl;
  out_h << "#include <vector>" << endl;
  out_h << "#include <windows.h>" << endl;

  // thrift headers
  out_h << "#include <Thrift/Thrift.h>" << endl;
  out_h << "#include <Thrift/Protocol.h>" << endl;
  out_h << "#include <Thrift/Transport.h>" << endl;

  // custom headers
  typedef vector<t_program*> IncludesList;
  const IncludesList& includes = program_->get_includes();
  IncludesList::const_iterator i;
  for (i = includes.begin(); i != includes.end(); ++i) {
    vector<string> ns;
    parse_namespace((*i)->get_namespace("cppw"), ns);
    if (ns.empty())
      continue;
    out_h << "#include <" << ns.front();
    for (size_t j = 1; j != ns.size(); ++j)
      out_h << "/" << ns.at(j);
    out_h << ".h>" << endl;
  }

  out_h << endl;
}

void t_cppw_generator::close_generator() {
  f_group_.close();
}

void t_cppw_generator::generate_typedef(t_typedef* ttypedef) {
  ofstream out_h;
  create_header(ttypedef->get_symbolic(), out_h);
  t_indent indent_h;

  start_cppw_namespace(out_h);

  out_h << endl;
  indent_h(out_h) << "typedef " << type_name(ttypedef->get_type(), true) << " " << ttypedef->get_symbolic() << ";" << endl << endl;

  end_cppw_namespace(out_h);

  out_h.close();
}

void t_cppw_generator::generate_enum(t_enum* tenum) {
  ofstream out_h;
  create_header(tenum->get_name(), out_h);
  t_indent indent_h;

  start_cppw_namespace(out_h);

  // begin enumeration
  indent_h(out_h) << "enum " << tenum->get_name() << "\n";
  indent_h.scope_up(out_h);

  // enumeration members
  vector<t_enum_value*> constants = tenum->get_constants();
  vector<t_enum_value*>::iterator c_iter;
  int value = -1;
  for (c_iter = constants.begin(); c_iter != constants.end(); ++c_iter)
  {
    if ((*c_iter)->has_value()) {
      value = (*c_iter)->get_value();
    } else {
      ++value;
    }

    indent_h(out_h) << (*c_iter)->get_name() << " = " << value << "," << endl;
  }

  // end enumeration
  indent_h.scope_down(out_h);
  out_h << ";" << endl;

  end_cppw_namespace(out_h);

}

void t_cppw_generator::generate_consts(vector<t_const*> consts) {
  vector<t_const*>::iterator c_iter;

  if (consts.empty()){
    return;
  }

  // header
  ofstream out_h;
  create_header("Constants", out_h);
  t_indent indent_h;

  start_cppw_namespace(out_h);

  indent_h(out_h) << "class Constants" << endl;
  indent_h(out_h) << "{" << endl;
  indent_h(out_h) << "public:" << endl;
  indent_h.up();

  // implementation
  ofstream out_cpp;
  create_implementation("Constants", out_cpp);
  t_indent indent_cpp;

  // constructor declaration
  indent_h(out_h) << "Constants();" << endl << endl;

  // constructor definition
  indent_cpp(out_cpp) << "Constants::Constants()" << endl;
  indent_cpp.scope_up(out_cpp);
  for (c_iter = consts.begin(); c_iter != consts.end(); ++c_iter) {
    print_const_value
      ( out_cpp
      , indent_cpp
      , (*c_iter)->get_name()
      , (*c_iter)->get_type()
      , (*c_iter)->get_value()
      );
  }
  indent_cpp.scope_down(out_cpp);

  // fields
  for (c_iter = consts.begin(); c_iter != consts.end(); ++c_iter) {
    string  name = (*c_iter)->get_name();
    t_type* type = (*c_iter)->get_type();
    indent_h(out_h) << type_name(type) << " " << name << ";" << endl;

  }

  indent_h.down();
  indent_h(out_h) << "};" << endl;

  indent_h(out_h) << "const Constants constants;" << endl;

  end_cppw_namespace(out_h);
  out_h.close();
}

void t_cppw_generator::print_const_def_value(ofstream& out_h, t_indent & indent_h, string name, t_type* type, t_const_value* value) {
  if (type->is_struct() || type->is_xception()) {
    const vector<t_field*>& fields = ((t_struct*)type)->get_members();
    vector<t_field*>::const_iterator f_iter;
    const map<t_const_value*, t_const_value*>& val = value->get_map();
    map<t_const_value*, t_const_value*>::const_iterator v_iter;
    for (v_iter = val.begin(); v_iter != val.end(); ++v_iter) {
      t_type* field_type = NULL;
      for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
        if ((*f_iter)->get_name() == v_iter->first->get_string()) {
          field_type = (*f_iter)->get_type();
        }
      }
      if (field_type == NULL) {
        throw "type error: " + type->get_name() + " has no field " + v_iter->first->get_string();
      }
      string val = render_const_value(out_h, indent_h, name, field_type, v_iter->second);
      indent_h(out_h) << name << "." << v_iter->first->get_string() << " = " << val << ";" << endl;
    }
  } else if (type->is_map()) {
    t_type* ktype = ((t_map*)type)->get_key_type();
    t_type* vtype = ((t_map*)type)->get_val_type();
    const map<t_const_value*, t_const_value*>& val = value->get_map();
    map<t_const_value*, t_const_value*>::const_iterator v_iter;
    for (v_iter = val.begin(); v_iter != val.end(); ++v_iter) {
      string key = render_const_value(out_h, indent_h, name, ktype, v_iter->first);
      string val = render_const_value(out_h, indent_h, name, vtype, v_iter->second);
      indent_h(out_h) << name << "[" << key << "]" << " = " << val << ";" << endl;
    }
  } else if (type->is_list() || type->is_set()) {
    t_type* etype;
    if (type->is_list()) {
      etype = ((t_list*)type)->get_elem_type();
    } else {
      etype = ((t_set*)type)->get_elem_type();
    }

    const vector<t_const_value*>& val = value->get_list();
    vector<t_const_value*>::const_iterator v_iter;
    for (v_iter = val.begin(); v_iter != val.end(); ++v_iter) {
      string val = render_const_value(out_h, indent_h, name, etype, *v_iter);
      indent_h(out_h) << name << ".push_back(" << val << ");" << endl;
    }
  }
}

void t_cppw_generator::print_const_constructor(ofstream& out_h, t_indent & indent_h, vector<t_const*> consts) {
  indent_h(out_h) << "static Constants()" << endl;
  indent_h.scope_up(out_h);
  vector<t_const*>::iterator c_iter;
  for (c_iter = consts.begin(); c_iter != consts.end(); ++c_iter) {
    string name = (*c_iter)->get_name();
    t_type* type = (*c_iter)->get_type();
    t_const_value* value = (*c_iter)->get_value();

    print_const_def_value(out_h, indent_h, name, type, value);
  }
  indent_h.scope_down(out_h);
}


/**
 * Prints the value of a constant with the given type. Note that type checking
 * is NOT performed in this function as it is always run beforehand using the
 * validate_types method in main.cc
 */
void t_cppw_generator::print_const_value(ofstream& out_h, t_indent & indent_h, string name, t_type* type, t_const_value* value) {
  type = get_true_type(type);
  if (type->is_base_type()) {
    string v2 = render_const_value(out_h, indent_h, name, type, value);
    indent_h(out_h) << name << " = " << v2 << ";" << endl << endl;
  } else if (type->is_enum()) {
    indent_h(out_h) << name << " = (" << type_name(type) << ")" << value->get_integer() << ";" << endl << endl;
  } else if (type->is_struct() || type->is_xception()) {
    const vector<t_field*>& fields = ((t_struct*)type)->get_members();
    vector<t_field*>::const_iterator f_iter;
    const map<t_const_value*, t_const_value*>& val = value->get_map();
    map<t_const_value*, t_const_value*>::const_iterator v_iter;
    for (v_iter = val.begin(); v_iter != val.end(); ++v_iter) {
      t_type* field_type = NULL;
      for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
        if ((*f_iter)->get_name() == v_iter->first->get_string()) {
          field_type = (*f_iter)->get_type();
        }
      }
      if (field_type == NULL) {
        throw "type error: " + type->get_name() + " has no field " + v_iter->first->get_string();
      }
      string val = render_const_value(out_h, indent_h, name, field_type, v_iter->second);
      indent_h(out_h) << name << "." << v_iter->first->get_string() << " = " << val << ";" << endl;
      indent_h(out_h) << name << ".__isset." << v_iter->first->get_string() << " = true;" << endl;
    }
    out_h << endl;
  } else if (type->is_map()) {
    t_type* ktype = ((t_map*)type)->get_key_type();
    t_type* vtype = ((t_map*)type)->get_val_type();
    const map<t_const_value*, t_const_value*>& val = value->get_map();
    map<t_const_value*, t_const_value*>::const_iterator v_iter;
    for (v_iter = val.begin(); v_iter != val.end(); ++v_iter) {
      string key = render_const_value(out_h, indent_h, name, ktype, v_iter->first);
      string val = render_const_value(out_h, indent_h, name, vtype, v_iter->second);
      indent_h(out_h) << name << ".insert(std::make_pair(" << key << ", " << val << "));" << endl;
    }
    out_h << endl;
  } else if (type->is_list()) {
    t_type* etype = ((t_list*)type)->get_elem_type();
    const vector<t_const_value*>& val = value->get_list();
    vector<t_const_value*>::const_iterator v_iter;
    for (v_iter = val.begin(); v_iter != val.end(); ++v_iter) {
      string val = render_const_value(out_h, indent_h, name, etype, *v_iter);
      indent_h(out_h) << name << ".push_back(" << val << ");" << endl;
    }
    out_h << endl;
  } else if (type->is_set()) {
    t_type* etype = ((t_set*)type)->get_elem_type();
    const vector<t_const_value*>& val = value->get_list();
    vector<t_const_value*>::const_iterator v_iter;
    for (v_iter = val.begin(); v_iter != val.end(); ++v_iter) {
      string val = render_const_value(out_h, indent_h, name, etype, *v_iter);
      indent_h(out_h) << name << ".insert(" << val << ");" << endl;
    }
    out_h << endl;
  } else {
    throw "INVALID TYPE IN print_const_value: " + type->get_name();
  }
}

string t_cppw_generator::render_const_value(ofstream& out_h, t_indent& indent_h, string name, t_type* type, t_const_value* value) {
  ostringstream render;

  if (type->is_base_type()) {
    t_base_type::t_base tbase = ((t_base_type*)type)->get_base();
    switch (tbase) {
    case t_base_type::TYPE_STRING:
      render << "Thrift::Protocol::TString(L\"" << get_escaped_string(value) << "\")";
      break;
    case t_base_type::TYPE_BOOL:
      render << ((value->get_integer() > 0) ? "true" : "false");
      break;
    case t_base_type::TYPE_BYTE:
    case t_base_type::TYPE_I16:
    case t_base_type::TYPE_I32:
      render << value->get_integer();
      break;
    case t_base_type::TYPE_I64:
      render << value->get_integer() << "LL";
      break;
    case t_base_type::TYPE_DOUBLE:
      if (value->get_type() == t_const_value::CV_INTEGER) {
        render << value->get_integer();
      } else {
        render << value->get_double();
      }
      break;
    default:
      throw "compiler error: no const of base type " + t_base_type::t_base_name(tbase);
    }
  } else if (type->is_enum()) {
    render << "(" << type_name(type) << ")" << value->get_integer();
  } else {
    string t = tmp("tmp");
    indent_h(out_h) << type_name(type) << " " << t << ";" << endl;
    print_const_value(out_h, indent_h, t, type, value);
    render << t;
  }

  return render.str();
}

void t_cppw_generator::generate_struct(t_struct* tstruct) {
  generate_cppw_struct(tstruct, false);
}

void t_cppw_generator::generate_xception(t_struct* txception) {
  generate_cppw_struct(txception, true);
}

void t_cppw_generator::generate_cppw_struct(t_struct* tstruct, bool is_exception) {
  ofstream out_h;
  create_header(tstruct->get_name(), out_h);
  t_indent indent_h;
  out_h << endl;

  ofstream out_cpp;
  create_implementation(tstruct->get_name(), out_cpp);
  t_indent indent_cpp;

  generate_cppw_struct_definition(out_h, indent_h, out_cpp, indent_cpp, tstruct, is_exception);
}

void t_cppw_generator::generate_cppw_struct_definition(ofstream& out_h, t_indent & indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, bool is_exception, t_type* parent, bool is_result) {

  if (!parent)
    start_cppw_namespace(out_h);
  out_h << endl;

  bool is_final = (tstruct->annotations_.find("final") != tstruct->annotations_.end());

  // class start
  indent_h(out_h) << "class " << tstruct->get_name();
  if (is_exception)
    indent_h(out_h) << " : public Thrift::TException";
  indent_h(out_h) << endl;
  indent_h(out_h) << "{" << endl;
  indent_h(out_h) << "public:" << endl << endl;
  indent_h.up();

  const vector<t_field*>& members = tstruct->get_members();
  vector<t_field*>::const_iterator m_iter;

  // check whether there are any non-required fields
  bool has_nonrequired_fields = false;
  for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
    if ((*m_iter)->get_req() != t_field::T_REQUIRED) {
      has_nonrequired_fields = true;
      break;
    }
  }

  // Isset struct has boolean fields for non-required fields
  if (has_nonrequired_fields) {
    indent_h(out_h) << "struct Isset" << endl;
    indent_h.scope_up(out_h);

    for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
      if ((*m_iter)->get_req() != t_field::T_REQUIRED)
        indent_h(out_h) << "bool " << (*m_iter)->get_name() << ";" << endl;
    }

    indent_h.down();
    indent_h(out_h) << "};" << endl << endl;
  }

  // fields
  for (m_iter = members.begin(); m_iter != members.end(); ++m_iter)
    indent_h(out_h) << declare_field(*m_iter, false) << endl;
  out_h << endl;
  if (has_nonrequired_fields)
    indent_h(out_h) << "Isset __isset;" << endl << endl;

  // constructor
  indent_h(out_h) << tstruct->get_name() << "();" << endl;

  indent_cpp(out_cpp);
  if (parent)
    out_cpp << parent->get_name() << "::";
  out_cpp << tstruct->get_name() << "::" << tstruct->get_name() << "()" << endl;

  indent_cpp.scope_up(out_cpp);

  for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
    if ((*m_iter)->get_value() != NULL) {
      print_const_value
        ( out_cpp
        , indent_cpp
        , (*m_iter)->get_name()
        , (*m_iter)->get_type()
        , (*m_iter)->get_value()
        );
    }
  }

  if (has_nonrequired_fields)
    indent_cpp(out_cpp) << "::ZeroMemory(&__isset, sizeof(Isset));" << endl;

  indent_cpp.scope_down(out_cpp);
  indent_cpp(out_cpp) << endl;

  // virtual distructor for extensible classes
  if (!is_final)
    indent_h(out_h) << "virtual ~" << tstruct->get_name() << "() throw() {}" << endl << endl;

  // class contents
  generate_cppw_struct_reader(out_h, indent_h, out_cpp, indent_cpp, tstruct, parent);
  if (is_result) {
    generate_cppw_struct_result_writer(out_h, indent_h, out_cpp, indent_cpp, tstruct, parent);
  } else {
    generate_cppw_struct_writer(out_h, indent_h, out_cpp, indent_cpp, tstruct, parent);
  }

  // end class
  indent_h.down();
  indent_h(out_h) << "};" << endl;

  if (!parent)
    end_cppw_namespace(out_h);
}

void t_cppw_generator::generate_cppw_struct_reader(ofstream& out_h, t_indent & indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, t_type* parent) {
  // header
  indent_h(out_h) << "void Read(Thrift::Protocol::TProtocol & iprot);" << endl;

  // implementation
  indent_cpp(out_cpp) << "void ";
  if (parent)
    out_cpp << parent->get_name() << "::";
  out_cpp << tstruct->get_name() << "::Read(Thrift::Protocol::TProtocol & iprot)" << endl;
  indent_cpp.scope_up(out_cpp);

  const vector<t_field*>& fields = tstruct->get_members();
  vector<t_field*>::const_iterator f_iter;

  indent_cpp(out_cpp) << "Thrift::Protocol::TStruct struc;" << endl;
  indent_cpp(out_cpp) << "iprot.ReadStructBegin(struc);" << endl;

  indent_cpp(out_cpp) << "for (;;)" << endl;
  indent_cpp.scope_up(out_cpp);

  indent_cpp(out_cpp) << "Thrift::Protocol::TField field;" << endl;
  indent_cpp(out_cpp) << "iprot.ReadFieldBegin(field);" << endl;

  indent_cpp(out_cpp) << "if (field.GetType() == Thrift::Protocol::TypeStop)" << endl;
  indent_cpp.up();
  indent_cpp(out_cpp) << "break;" << endl;
  indent_cpp.down();

  indent_cpp(out_cpp) << "switch (field.GetID())" << endl;
  indent_cpp(out_cpp) << "{" << endl;

  for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
    indent_cpp(out_cpp) << "case " << (*f_iter)->get_key() << ":" << endl;
    indent_cpp.up();

    indent_cpp(out_cpp) << "if (field.GetType() == " << type_to_enum((*f_iter)->get_type()) << ")" << endl;
    indent_cpp.scope_up(out_cpp);
    generate_deserialize_field(out_cpp, indent_cpp, *f_iter, "this->");
    if ((*f_iter)->get_req() != t_field::T_REQUIRED)
      indent_cpp(out_cpp) << "this->__isset." << (*f_iter)->get_name() << " = true;" << endl;
    indent_cpp.scope_down(out_cpp);

    indent_cpp(out_cpp) << "else" << endl;
    indent_cpp.scope_up(out_cpp);
    indent_cpp(out_cpp) << "Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());" << endl;
    indent_cpp.scope_down(out_cpp);

    indent_cpp(out_cpp) << "break;" << endl;
    indent_cpp.down();
  }

  indent_cpp(out_cpp) << "default: " << endl;
  indent_cpp.up();
  indent_cpp(out_cpp) << "Thrift::Protocol::TProtocolUtil::Skip(iprot, field.GetType());" << endl;
  indent_cpp(out_cpp) << "break;" << endl;
  indent_cpp.scope_down(out_cpp);

  indent_cpp(out_cpp) << "iprot.ReadFieldEnd();" << endl;

  indent_cpp.scope_down(out_cpp);

  indent_cpp(out_cpp) << "iprot.ReadStructEnd();" << endl;

  indent_cpp.scope_down(out_cpp);
  out_cpp << endl;

}

void t_cppw_generator::generate_cppw_struct_writer(ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, t_type* parent) {
  // header
  indent_h(out_h) << "void Write(Thrift::Protocol::TProtocol & oprot);" << endl;

  // implementation
  indent_cpp(out_cpp) << "void ";
  if (parent)
    out_cpp << parent->get_name() << "::";
  out_cpp << tstruct->get_name() << "::Write(Thrift::Protocol::TProtocol & oprot)" << endl;
  indent_cpp.scope_up(out_cpp);

  string name = tstruct->get_name();
  const vector<t_field*>& fields = tstruct->get_sorted_members();
  vector<t_field*>::const_iterator f_iter;

  indent_cpp(out_cpp) << "Thrift::Protocol::TStruct struc;" << endl;
  indent_cpp(out_cpp) << "struc.SetName(L\"" << name << "\");" << endl;
  indent_cpp(out_cpp) << "oprot.WriteStructBegin(struc);" << endl;

  if (fields.size() > 0) {
    for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
      if ((*f_iter)->get_req() != t_field::T_REQUIRED)
        indent_cpp(out_cpp) << "if (__isset." << (*f_iter)->get_name() << ")" << endl;
      indent_cpp.scope_up(out_cpp);

      indent_cpp(out_cpp) << "Thrift::Protocol::TField field;" << endl;
      indent_cpp(out_cpp) << "field.SetName(L\"" << (*f_iter)->get_name() << "\");" << endl;
      indent_cpp(out_cpp) << "field.SetType(" << type_to_enum((*f_iter)->get_type()) << ");" << endl;
      indent_cpp(out_cpp) << "field.SetID(" << (*f_iter)->get_key() << ");" << endl;
      indent_cpp(out_cpp) << "oprot.WriteFieldBegin(field);" << endl;

      generate_serialize_field(out_cpp, indent_cpp, *f_iter, "this->");

      indent_cpp(out_cpp) << "oprot.WriteFieldEnd();" << endl;

      indent_cpp.scope_down(out_cpp);
    }
  }

  indent_cpp(out_cpp) << "oprot.WriteFieldStop();" << endl;
  indent_cpp(out_cpp) << "oprot.WriteStructEnd();" << endl;

  indent_cpp.scope_down(out_cpp);
  out_cpp << endl;
}

void t_cppw_generator::generate_cppw_struct_result_writer(ofstream& out_h, t_indent & indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_struct* tstruct, t_type* parent) {
  // header
  indent_h(out_h) << "void Write(Thrift::Protocol::TProtocol & oprot);" << endl;

  // implementation
  indent_cpp(out_cpp) << "void ";
  if (parent)
    out_cpp << parent->get_name() << "::";
  out_cpp << tstruct->get_name() << "::Write(Thrift::Protocol::TProtocol & oprot)" << endl;
  indent_cpp.scope_up(out_cpp);

  string name = tstruct->get_name();
  const vector<t_field*>& fields = tstruct->get_sorted_members();
  vector<t_field*>::const_iterator f_iter;

  indent_cpp(out_cpp) << "Thrift::Protocol::TStruct struc;" << endl;
  indent_cpp(out_cpp) << "struc.SetName(L\"" << name << "\");" << endl;
  indent_cpp(out_cpp) << "oprot.WriteStructBegin(struc);" << endl;

  if (fields.size() > 0) {
    bool first = true;
    for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
      if (first) {
        first = false;
        out_cpp << endl;
        indent_cpp(out_cpp) << "if ";
      } else {
        out_cpp << " else if ";
      }

      out_cpp << "(this->__isset." << (*f_iter)->get_name() << ")" << endl;
      indent_cpp.scope_up(out_cpp);

      indent_cpp(out_cpp) << "Thrift::Protocol::TField field;" << endl;
      indent_cpp(out_cpp) << "field.SetName(L\"" << (*f_iter)->get_name() << "\");" << endl;
      indent_cpp(out_cpp) << "field.SetType(" << type_to_enum((*f_iter)->get_type()) << ");" << endl;
      indent_cpp(out_cpp) << "field.SetID(" << (*f_iter)->get_key() << ");" << endl;
      indent_cpp(out_cpp) << "oprot.WriteFieldBegin(field);" << endl;

      generate_serialize_field(out_cpp, indent_cpp, *f_iter, "this->");

      indent_cpp(out_cpp) << "oprot.WriteFieldEnd();" << endl;

      indent_cpp.scope_down(out_cpp);
    }
  }

  out_cpp << endl;
  indent_cpp(out_cpp) << "oprot.WriteFieldStop();" << endl;
  indent_cpp(out_cpp) << "oprot.WriteStructEnd();" << endl;

  indent_cpp.scope_down(out_cpp);
}

void t_cppw_generator::generate_service(t_service* tservice) {
  // header
  ofstream out_h;
  create_header(service_name_, out_h);
  t_indent indent_h;

  start_cppw_namespace(out_h);

  indent_h(out_h) << "class " << service_name_ << endl;
  indent_h(out_h) << "{" << endl;
  indent_h(out_h) << "public:" << endl;

  indent_h.up();

  // implementation
  ofstream out_cpp;
  create_implementation(service_name_, out_cpp);
  t_indent indent_cpp;

  // content
  generate_service_interface (out_h, indent_h, out_cpp, indent_cpp, tservice);
  generate_service_client    (out_h, indent_h, out_cpp, indent_cpp, tservice);
  generate_service_server    (out_h, indent_h, out_cpp, indent_cpp, tservice);
  generate_service_helpers   (out_h, indent_h, out_cpp, indent_cpp, tservice);

  // end header
  indent_h.down();
  indent_h(out_h) << "};" << endl;
  end_cppw_namespace(out_h);
}

void t_cppw_generator::generate_service_interface(ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice) {
  string extends_iface = "";
  if (tservice->get_extends() != NULL) {
    string extends = type_name(tservice->get_extends());
    extends_iface = " : public " + extends + ".Iface";
  }

  // begin class
  indent_h(out_h) << "class Iface" << extends_iface <<endl;
  indent_h(out_h) << "{" << endl;
  indent_h(out_h) << "public:" << endl;
  indent_h.up();

  // member functions
  vector<t_function*> functions = tservice->get_functions();
  vector<t_function*>::iterator f_iter;
  for (f_iter = functions.begin(); f_iter != functions.end(); ++f_iter)
    indent_h(out_h) << "virtual " << function_signature(*f_iter) << " = 0;" << endl;

  // end class
  indent_h.down();
  indent_h(out_h) << "};" << endl << endl;
}

void t_cppw_generator::generate_service_helpers(ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice) {
  vector<t_function*> functions = tservice->get_functions();
  vector<t_function*>::iterator f_iter;

  for (f_iter = functions.begin(); f_iter != functions.end(); ++f_iter) {
    t_struct* ts = (*f_iter)->get_arglist();
    generate_cppw_struct_definition(out_h, indent_h, out_cpp, indent_cpp, ts, false, tservice);
    generate_function_helpers(out_h, indent_h, out_cpp, indent_cpp, tservice, *f_iter);
  }
}


void t_cppw_generator::generate_service_client(ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice) {
  string extends;
  string extends_client;
  if (tservice->get_extends() != NULL) {
    extends = type_name(tservice->get_extends());
    extends_client = string("public ") + extends + ".Client, ";
  }

  // begin class
  indent_h(out_h) << "class Client : " << extends_client << "public Iface" << endl;
  indent_h(out_h) << "{" << endl;
  indent_h(out_h) << "public:" << endl << endl;
  indent_h.up();

  // constructor from one protocol
  indent_h(out_h) << "Client(Thrift::Protocol::TProtocol & prot) : iprot_(prot), oprot_(prot) { seqid_ = 0; }" << endl << endl;

  // constructor from two protocols
  indent_h(out_h) << "Client(Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot) : ";
  if (!extends.empty())
    out_h << "__super(iprot, oprot)";
  else
    out_h << "iprot_(iprot), oprot_(oprot)";
  out_h << " { seqid_ = 0; }" << endl << endl;

  // protocols with getters
  if (extends.empty()) {
    indent_h.down();
    indent_h(out_h) << "private:" << endl << endl;
    indent_h.up();
    indent_h(out_h) << "Thrift::Protocol::TProtocol & iprot_;" << endl;
    indent_h(out_h) << "Thrift::Protocol::TProtocol & oprot_;" << endl;
    indent_h(out_h) << "int seqid_;" << endl << endl;

    indent_h.down();
    indent_h(out_h) << "public:" << endl << endl;
    indent_h.up();
    indent_h(out_h) << "Thrift::Protocol::TProtocol & GetInputProtocol() { return iprot_; }" << endl;
    indent_h(out_h) << "Thrift::Protocol::TProtocol & GetOutputProtocol() { return oprot_; }" << endl;
    out_h << endl;
  }

  // monster loop
  indent_h.down();
  indent_h(out_h) << "public:" << endl << endl;
  indent_h.up();
  vector<t_function*> functions = tservice->get_functions();
  vector<t_function*>::const_iterator f_iter;
  for (f_iter = functions.begin(); f_iter != functions.end(); ++f_iter) {
    string funname = (*f_iter)->get_name();

    // main function implementation
    indent_h(out_h) << function_signature(*f_iter) << ";" << endl;

    indent_cpp(out_cpp) << function_signature(*f_iter, service_name_ + "::Client") << endl;
    indent_cpp.scope_up(out_cpp);
    indent_cpp(out_cpp) << "send_" << funname << "(";

    t_struct* arg_struct = (*f_iter)->get_arglist();

    const vector<t_field*>& fields = arg_struct->get_members();
    vector<t_field*>::const_iterator fld_iter;
    bool first = true;
    for (fld_iter = fields.begin(); fld_iter != fields.end(); ++fld_iter) {
      if (first) {
        first = false;
      } else {
        out_cpp << ", ";
      }
      out_cpp << (*fld_iter)->get_name();
    }
    out_cpp << ");" << endl;

    if (!(*f_iter)->is_oneway()) {
      indent_cpp(out_cpp);
      if (!(*f_iter)->get_returntype()->is_void()) {
        out_cpp << "return ";
      }
      out_cpp << "recv_" << funname << "();" << endl;
    }
    indent_cpp.scope_down(out_cpp);
    out_cpp << endl;

    // send_ function implementation
    t_function send_function(g_type_void,
        string("send_") + (*f_iter)->get_name(),
        (*f_iter)->get_arglist());

    string argsname = (*f_iter)->get_name() + "_args";

    indent_h(out_h) << function_signature(&send_function) << ";" << endl;

    indent_cpp(out_cpp) << function_signature(&send_function, service_name_ + "::Client") << endl;
    indent_cpp.scope_up(out_cpp);

    indent_cpp(out_cpp) << "oprot_.WriteMessageBegin(Thrift::Protocol::TMessage(L\"" << funname << "\", Thrift::Protocol::MessageCall, seqid_));" << endl;
    indent_cpp(out_cpp) << argsname << " args;" << endl;

    for (fld_iter = fields.begin(); fld_iter != fields.end(); ++fld_iter) {
      indent_cpp(out_cpp) << "args." << (*fld_iter)->get_name() << " = " << (*fld_iter)->get_name() << ";" << endl;
      if ((*fld_iter)->get_req() != t_field::T_REQUIRED)
        indent_cpp(out_cpp) << "args.__isset." << (*fld_iter)->get_name() << " = true;" << endl;
    }

    indent_cpp(out_cpp) << "args.Write(oprot_);" << endl;
    indent_cpp(out_cpp) << "oprot_.WriteMessageEnd();" << endl;
    indent_cpp(out_cpp) << "oprot_.GetTransport().Flush();" << endl;

    indent_cpp.scope_down(out_cpp);
    out_cpp << endl;

    // recv_ function implementation
    if (!(*f_iter)->is_oneway()) {
      string resultname = (*f_iter)->get_name() + "_result";

      t_struct noargs(program_);
      t_function recv_function((*f_iter)->get_returntype(),
          string("recv_") + (*f_iter)->get_name(),
          &noargs,
          (*f_iter)->get_xceptions());

      indent_h(out_h) << function_signature(&recv_function) << ";" << endl;

      indent_cpp(out_cpp) << function_signature(&recv_function, service_name_ + "::Client") << endl;
      indent_cpp.scope_up(out_cpp);

      indent_cpp(out_cpp) << "Thrift::Protocol::TMessage msg;" << endl;
      indent_cpp(out_cpp) << "iprot_.ReadMessageBegin(msg);" << endl;
      indent_cpp(out_cpp) << "if (msg.GetType() == Thrift::Protocol::MessageException)" << endl;
      indent_cpp.scope_up(out_cpp);
      indent_cpp(out_cpp) << "Thrift::TApplicationException x = Thrift::TApplicationException::Read(iprot_);" << endl;
      indent_cpp(out_cpp) << "iprot_.ReadMessageEnd();" << endl;
      indent_cpp(out_cpp) << "throw x;" << endl;
      indent_cpp.scope_down(out_cpp);
      indent_cpp(out_cpp) << resultname << " result;" << endl;
      indent_cpp(out_cpp) << "result.Read(iprot_);" << endl;
      indent_cpp(out_cpp) << "iprot_.ReadMessageEnd();" << endl;

      if (!(*f_iter)->get_returntype()->is_void()) {
        indent_cpp(out_cpp) << "if (result.__isset.success)" << endl;
        indent_cpp.scope_up(out_cpp);
        indent_cpp(out_cpp) << "return result.success;" << endl;
        indent_cpp.scope_down(out_cpp);
      }

      t_struct *xs = (*f_iter)->get_xceptions();

      const vector<t_field*>& xceptions = xs->get_members();
      vector<t_field*>::const_iterator x_iter;
      for (x_iter = xceptions.begin(); x_iter != xceptions.end(); ++x_iter) {
        indent_cpp(out_cpp) << "if (result.__isset." << (*x_iter)->get_name() << ")" << endl;
        indent_cpp.scope_up(out_cpp);
        indent_cpp(out_cpp) << "throw result." << (*x_iter)->get_name() << ";" << endl;
        indent_cpp.scope_down(out_cpp);
      }

      if ((*f_iter)->get_returntype()->is_void()) {
        indent_cpp(out_cpp) << "return;" << endl;
      } else {
        indent_cpp(out_cpp) << "throw Thrift::TApplicationException(Thrift::TApplicationException::MissingResult, L\"" << (*f_iter)->get_name() << " failed: unknown result\");" << endl;
      }

      indent_cpp.scope_down(out_cpp);
      out_cpp << endl;
    }
  }

  // end class
  indent_h.down();
  indent_h(out_h) << "};" << endl << endl;
}


void t_cppw_generator::generate_service_server(ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice) {
  vector<t_function*> functions = tservice->get_functions();
  vector<t_function*>::iterator f_iter;

  string extends = "";
  string extends_processor = "";
  if (tservice->get_extends() != NULL) {
    extends = type_name(tservice->get_extends());
    extends_processor = "public " + extends + ".Processor, ";
  }

  // begin class
  indent_h(out_h) << "class Processor : " << extends_processor << "public Thrift::TProcessor" << endl;
  indent_h(out_h) << "{" << endl;
  indent_h(out_h) << "public:" << endl << endl;
  indent_h.up();

  // constructor
  indent_h(out_h) << "Processor(Iface & iface);" ;

  indent_cpp(out_cpp) << service_name_ << "::Processor::Processor(Iface & iface)" ;
  if (!extends.empty())
    out_cpp << " : __super(iface)";
  else
    out_cpp << " : iface_(iface)";
  out_cpp << endl;
  indent_cpp.scope_up(out_cpp);
  for (f_iter = functions.begin(); f_iter != functions.end(); ++f_iter) {
    indent_cpp(out_cpp) << "processMap_[L\"" << (*f_iter)->get_name() << "\"] = &Processor::" << (*f_iter)->get_name() << "_Process;" << endl;
  }
  indent_cpp.scope_down(out_cpp);
  out_cpp << endl;

  // fields
  indent_h.down();
  indent_h(out_h) << "private:" << endl << endl;
  indent_h.up();
  if (extends.empty()) {
    indent_h(out_h) << "typedef void (" << namespace_prefix(namespaces_) << namespaces_.back() << "::Processor::*ProcessFunction)(int, Thrift::Protocol::TProtocol &, Thrift::Protocol::TProtocol &);" << endl;
    indent_h(out_h) << "typedef std::map<std::wstring, ProcessFunction> ProcessMap;" << endl;
    indent_h(out_h) << "ProcessMap processMap_;" << endl;
  }

  indent_h(out_h) << "Iface & iface_;" << endl;

  out_h << endl;

  // public
  indent_h.down();
  indent_h(out_h) << "public:" << endl << endl;
  indent_h.up();

  // Process function
  indent_h(out_h) << "bool Process(Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot);" << endl;

  indent_cpp(out_cpp) << "bool " << service_name_ << "::Processor::Process(Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)" << endl;
  indent_cpp.scope_up(out_cpp);

  indent_cpp(out_cpp) << "Thrift::Protocol::TMessage msg;" << endl;
  indent_cpp(out_cpp) << "iprot.ReadMessageBegin(msg);" << endl;

  indent_cpp(out_cpp) << "ProcessMap::iterator fn = processMap_.find(msg.GetName());" << endl;
  indent_cpp(out_cpp) << "if (fn == processMap_.end())" << endl;
  indent_cpp.scope_up(out_cpp);
  indent_cpp(out_cpp) << "Thrift::Protocol::TProtocolUtil::Skip(iprot, Thrift::Protocol::TypeStruct);" << endl;
  indent_cpp(out_cpp) << "iprot.ReadMessageEnd();" << endl;
  indent_cpp(out_cpp) << "Thrift::TApplicationException x(Thrift::TApplicationException::UnknownMethod, (std::wstring(L\"Invalid method name: '\") + msg.GetName() + L\"'\").c_str());" << endl;
  indent_cpp(out_cpp) << "oprot.WriteMessageBegin(Thrift::Protocol::TMessage(msg.GetName(), Thrift::Protocol::MessageException, msg.GetSeqID()));" << endl;
  indent_cpp(out_cpp) << "x.Write(oprot);" << endl;
  indent_cpp(out_cpp) << "oprot.WriteMessageEnd();" << endl;
  indent_cpp(out_cpp) << "oprot.GetTransport().Flush();" << endl;
  indent_cpp(out_cpp) << "return true;" << endl;
  indent_cpp.scope_down(out_cpp);
  indent_cpp(out_cpp) << "(this->*fn->second)(msg.GetSeqID(), iprot, oprot);" << endl;

  indent_cpp(out_cpp) << "return true;" << endl;

  indent_cpp.scope_down(out_cpp);
  out_cpp << endl;

  // process functions
  for (f_iter = functions.begin(); f_iter != functions.end(); ++f_iter)
    generate_process_function(out_h, indent_h, out_cpp, indent_cpp, tservice, *f_iter);

  // end class
  indent_h.down();
  indent_h(out_h) << "};" << endl << endl;
}

void t_cppw_generator::generate_function_helpers(ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_type* parent, t_function* tfunction) {
  if (tfunction->is_oneway()) {
    return;
  }

  t_struct result(program_, tfunction->get_name() + "_result");
  t_field success(tfunction->get_returntype(), "success", 0);
  if (!tfunction->get_returntype()->is_void())
    result.append(&success);

  t_struct *xs = tfunction->get_xceptions();
  const vector<t_field*>& fields = xs->get_members();
  vector<t_field*>::const_iterator f_iter;
  for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
    result.append(*f_iter);
  }

  generate_cppw_struct_definition(out_h, indent_h, out_cpp, indent_cpp, &result, false, parent, true);
}

void t_cppw_generator::generate_process_function(ofstream& out_h, t_indent& indent_h, ofstream& out_cpp, t_indent& indent_cpp, t_service* tservice, t_function* tfunction) {
  indent_h(out_h) << "void " << tfunction->get_name() << "_Process(int seqid, Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot);" << endl;

  indent_cpp(out_cpp) << "void " << service_name_ << "::Processor::" << tfunction->get_name() << "_Process(int seqid, Thrift::Protocol::TProtocol & iprot, Thrift::Protocol::TProtocol & oprot)" << endl;
  indent_cpp.scope_up(out_cpp);

  string argsname = tfunction->get_name() + "_args";
  string resultname = tfunction->get_name() + "_result";

  indent_cpp(out_cpp) << argsname << " args;" << endl;
  indent_cpp(out_cpp) << "args.Read(iprot);" << endl;
  indent_cpp(out_cpp) << "iprot.ReadMessageEnd();" << endl;

  t_struct* xs = tfunction->get_xceptions();
  const vector<t_field*>& xceptions = xs->get_members();
  vector<t_field*>::const_iterator x_iter;

  if (!tfunction->is_oneway()) {
    indent_cpp(out_cpp) << resultname << " result;" << endl;
  }

  if (xceptions.size() > 0) {
    indent_cpp(out_cpp) << "try" << endl;
    indent_cpp.scope_up(out_cpp);
  }

  t_struct* arg_struct = tfunction->get_arglist();
  const vector<t_field*>& fields = arg_struct->get_members();
  vector<t_field*>::const_iterator f_iter;

  indent_cpp(out_cpp);
  if (!tfunction->is_oneway() && !tfunction->get_returntype()->is_void()) {
    out_cpp << "result.success = ";
  }
  out_cpp << "iface_." << tfunction->get_name() << "(";
  bool first = true;
  for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
    if (first) {
      first = false;
    } else {
      out_cpp << ", ";
    }
    out_cpp << "args." << (*f_iter)->get_name();
  }
  out_cpp << ");" << endl;

  if (!tfunction->is_oneway() && xceptions.size() > 0) {
    indent_cpp.scope_down(out_cpp);
    for (x_iter = xceptions.begin(); x_iter != xceptions.end(); ++x_iter) {
      indent_cpp(out_cpp) << "catch (" << type_name((*x_iter)->get_type(), false, false) << " " << (*x_iter)->get_name() << ")" << endl;
      if (!tfunction->is_oneway()) {
        indent_cpp.scope_up(out_cpp);
        indent_cpp(out_cpp) << "result." << (*x_iter)->get_name() << " = " << (*x_iter)->get_name() << ";" << endl;
        indent_cpp.scope_down(out_cpp);
      }
    }
  }

  if (tfunction->is_oneway()) {
    indent_cpp(out_cpp) << "return;" << endl;
    indent_cpp.scope_down(out_cpp);

    return;
  }

  indent_cpp(out_cpp) << "oprot.WriteMessageBegin(Thrift::Protocol::TMessage(L\"" << tfunction->get_name() << "\", Thrift::Protocol::MessageReply, seqid)); " << endl;
  indent_cpp(out_cpp) << "result.Write(oprot);" << endl;
  indent_cpp(out_cpp) << "oprot.WriteMessageEnd();" << endl;
  indent_cpp(out_cpp) << "oprot.GetTransport().Flush();" << endl;

  indent_cpp.scope_down(out_cpp);

  out_cpp << endl;
}

void t_cppw_generator::generate_deserialize_field(ofstream& out_h, t_indent& indent_h, t_field* tfield, string prefix) {
  t_type* type = tfield->get_type();
  while (type->is_typedef()) {
    type = ((t_typedef*)type)->get_type();
  }

  if (type->is_void()) {
    throw "CANNOT GENERATE DESERIALIZE CODE FOR void TYPE: " + prefix + tfield->get_name();
  }

  string name = prefix + tfield->get_name();


  if (type->is_struct() || type->is_xception()) {
    generate_deserialize_struct(out_h, indent_h, (t_struct*)type, name);
  } else if (type->is_container()) {
    generate_deserialize_container(out_h, indent_h, type, name);
  } else if (type->is_base_type() || type->is_enum()) {
    t_base_type::t_base tbase = ((t_base_type*)type)->get_base();

    if (tbase == t_base_type::TYPE_STRING) {
      if (((t_base_type*)type)->is_binary()) {
        indent_h(out_h) << "iprot.ReadBinary(" << name << ");" << endl;
      } else {
        indent_h(out_h) << "iprot.ReadString(" << name << ");" << endl;
      }
    } else {
      indent_h(out_h) << name << " = ";

      if (type->is_enum())
        out_h << "(" << type_name(type, false, true) << ")";

      out_h << "iprot.";

      if (type->is_base_type()) {
        switch (tbase) {
          case t_base_type::TYPE_VOID:
            throw "compiler error: cannot serialize void field in a struct: " + name;
            break;
          case t_base_type::TYPE_BOOL:
            out_h << "ReadBool();";
            break;
          case t_base_type::TYPE_BYTE:
            out_h << "ReadByte();";
            break;
          case t_base_type::TYPE_I16:
            out_h << "ReadI16();";
            break;
          case t_base_type::TYPE_I32:
            out_h << "ReadI32();";
            break;
          case t_base_type::TYPE_I64:
            out_h << "ReadI64();";
            break;
          case t_base_type::TYPE_DOUBLE:
            out_h << "ReadDouble();";
            break;
          default:
            throw "compiler error: no C# name for base type " + tbase;
        }
      } else if (type->is_enum()) {
        out_h << "ReadI32();";
      }
      out_h << endl;
    }
  } else {
    printf("DO NOT KNOW HOW TO DESERIALIZE FIELD '%s' TYPE '%s'\n", tfield->get_name().c_str(), type_name(type).c_str());
  }
}

void t_cppw_generator::generate_deserialize_struct(ofstream& out_h, t_indent& indent_h, t_struct* tstruct, string prefix) {
  indent_h(out_h) << prefix << ".Read(iprot);" << endl;
}

void t_cppw_generator::generate_deserialize_container(ofstream& out_h, t_indent& indent_h, t_type* ttype, string prefix) {
  indent_h.scope_up(out_h);

  string obj;

  if (ttype->is_map()) {
    obj = tmp("_map");
  } else if (ttype->is_set()) {
    obj = tmp("_set");
  } else if (ttype->is_list()) {
    obj = tmp("_list");
  }

  if (ttype->is_map()) {
    indent_h(out_h) << "Thrift::Protocol::TMap " << obj << ";" << endl;
    indent_h(out_h) << "iprot.ReadMapBegin(" << obj << ");" << endl;
  } else if (ttype->is_set()) {
    indent_h(out_h) << "Thrift::Protocol::TSet " << obj << ";" << endl;
    indent_h(out_h) << "iprot.ReadSetBegin(" << obj << ");" << endl;
  } else if (ttype->is_list()) {
    indent_h(out_h) << "Thrift::Protocol::TList " << obj << ";" << endl;
    indent_h(out_h) << "iprot.ReadListBegin(" << obj << ");" << endl;
  }

  string i = tmp("_i");
  indent_h(out_h) << "for (int " << i << " = 0; " << i << " < " << obj << ".GetCount()" << "; " << "++" << i << ")" << endl;
  indent_h.scope_up(out_h);

  if (ttype->is_map()) {
    generate_deserialize_map_element(out_h, indent_h, (t_map*)ttype, prefix);
  } else if (ttype->is_set()) {
    generate_deserialize_set_element(out_h, indent_h, (t_set*)ttype, prefix);
  } else if (ttype->is_list()) {
    generate_deserialize_list_element(out_h, indent_h, (t_list*)ttype, prefix);
  }

  indent_h.scope_down(out_h);

  if (ttype->is_map()) {
    indent_h(out_h) << "iprot.ReadMapEnd();" << endl;
  } else if (ttype->is_set()) {
    indent_h(out_h) << "iprot.ReadSetEnd();" << endl;
  } else if (ttype->is_list()) {
    indent_h(out_h) << "iprot.ReadListEnd();" << endl;
  }

  indent_h.scope_down(out_h);
}

void t_cppw_generator::generate_deserialize_map_element(ofstream& out_h, t_indent& indent_h, t_map* tmap, string prefix) {
  string key = tmp("_key");
  string val = tmp("_val");

  t_field fkey(tmap->get_key_type(), key);
  t_field fval(tmap->get_val_type(), val);

  indent_h(out_h) << declare_field(&fkey) << endl;
  indent_h(out_h) << declare_field(&fval) << endl;

  generate_deserialize_field(out_h, indent_h, &fkey);
  generate_deserialize_field(out_h, indent_h, &fval);

  indent_h(out_h) << prefix << "[" << key << "] = " << val << ";" << endl;
}

void t_cppw_generator::generate_deserialize_set_element(ofstream& out_h, t_indent& indent_h, t_set* tset, string prefix) {
  string elem = tmp("_elem");
  t_field felem(tset->get_elem_type(), elem);

  indent_h(out_h) << declare_field(&felem, true) << endl;

  generate_deserialize_field(out_h, indent_h, &felem);

  indent_h(out_h) << prefix << ".push_back(" << elem << ");" << endl;
}

void t_cppw_generator::generate_deserialize_list_element(ofstream& out_h, t_indent& indent_h, t_list* tlist, string prefix) {
  string elem = tmp("_elem");
  t_field felem(tlist->get_elem_type(), elem);

  indent_h(out_h) << declare_field(&felem, true) << endl;

  generate_deserialize_field(out_h, indent_h, &felem);

  indent_h(out_h) << prefix << ".push_back(" << elem << ");" << endl;
}

void t_cppw_generator::generate_serialize_field(ofstream& out_h, t_indent& indent_h, t_field* tfield, string prefix) {
  t_type* type = tfield->get_type();
  while (type->is_typedef()) {
    type = ((t_typedef*)type)->get_type();
  }

  string name = prefix + tfield->get_name();

  if (type->is_void()) {
    throw "CANNOT GENERATE SERIALIZE CODE FOR void TYPE: " + name;
  }

  if (type->is_struct() || type->is_xception()) {
    generate_serialize_struct(out_h, indent_h, (t_struct*)type, name);
  } else if (type->is_container()) {
    generate_serialize_container(out_h, indent_h, type, name);
  } else if (type->is_base_type()) {
    t_base_type::t_base tbase = ((t_base_type*)type)->get_base();

    if (tbase == t_base_type::TYPE_STRING) {
      bool is_binary = ((t_base_type*)type)->is_binary();
      const char * fun = is_binary ? "WriteBinary" : "WriteString";
      indent_h(out_h) << "oprot." << fun << "(" << name << ");" << endl;
    } else {
      indent_h(out_h) << "oprot.";
      switch(tbase) {
        case t_base_type::TYPE_VOID:
          throw "compiler error: cannot serialize void field in a struct: " + name;
          break;
        case t_base_type::TYPE_BOOL:
          out_h << "WriteBool(" << name << ");";
          break;
        case t_base_type::TYPE_BYTE:
          out_h << "WriteByte(" << name << ");";
          break;
        case t_base_type::TYPE_I16:
          out_h << "WriteI16(" << name << ");";
          break;
        case t_base_type::TYPE_I32:
          out_h << "WriteI32(" << name << ");";
          break;
        case t_base_type::TYPE_I64:
          out_h << "WriteI64(" << name << ");";
          break;
        case t_base_type::TYPE_DOUBLE:
          out_h << "WriteDouble(" << name << ");";
          break;
        default:
          throw "compiler error: no C# name for base type " + tbase;
      }
      out_h << endl;
    }
  } else if (type->is_enum()) {
    indent_h(out_h) << "oprot.WriteI32((int)" << name << ");" << endl;
  } else {
    printf("DO NOT KNOW HOW TO SERIALIZE '%s%s' TYPE '%s'\n",
        prefix.c_str(),
        tfield->get_name().c_str(),
        type_name(type).c_str());
  }
}

void t_cppw_generator::generate_serialize_struct(ofstream& out_h, t_indent& indent_h, t_struct* tstruct, string prefix) {
  indent_h(out_h) << prefix << ".Write(oprot);" << endl;
}

void t_cppw_generator::generate_serialize_container(ofstream& out_h, t_indent& indent_h, t_type* ttype, string prefix) {
  indent_h.scope_up(out_h);

  if (ttype->is_map()) {
    indent_h(out_h) << "Thrift::Protocol::TMap map;" << endl;
    indent_h(out_h) << "map.SetKeyType(" << type_to_enum(((t_map*)ttype)->get_key_type()) << ");" << endl;
    indent_h(out_h) << "map.SetValueType("<< type_to_enum(((t_map*)ttype)->get_val_type()) << ");" << endl;
    indent_h(out_h) << "map.SetCount(" << prefix << ".size());" << endl;
    indent_h(out_h) << "oprot.WriteMapBegin(map);" << endl;
  } else if (ttype->is_set()) {
    indent_h(out_h) << "Thrift::Protocol::TSet set;" << endl;
    indent_h(out_h) << "set.SetElementType(" << type_to_enum(((t_set*)ttype)->get_elem_type()) << ");" << endl;
    indent_h(out_h) << "set.SetCount(" << prefix << ".size());" << endl;
    indent_h(out_h) << "oprot.WriteSetBegin(set);" << endl;
  } else if (ttype->is_list()) {
    indent_h(out_h) << "Thrift::Protocol::TList list;" << endl;
    indent_h(out_h) << "list.SetElementType(" << type_to_enum(((t_list*)ttype)->get_elem_type()) << ");" << endl;
    indent_h(out_h) << "list.SetCount(" << prefix << ".size());" << endl;
    indent_h(out_h) << "oprot.WriteListBegin(list);" << endl;
  }

  string iter = tmp("_iter");
  if (ttype->is_map()) {
    indent_h(out_h)
      << "for ("
      << "std::map<" << type_name(((t_map*)ttype)->get_key_type())
      <<  ", " << type_name(((t_map*)ttype)->get_val_type()) << " >::iterator "
      << iter  << "(" << prefix << ".begin()), "
      << "end" << "(" << prefix << ".end()); "
      << iter << " != end; "
      << "++" << iter << ")";
  } else if (ttype->is_set()) {
    indent_h(out_h)
      << "for ("
      << "std::set<" << type_name(((t_set*)ttype)->get_elem_type()) << " >::iterator "
      << iter  << "(" << prefix << ".begin()), "
      << "end" << "(" << prefix << ".end()); "
      << iter << " != end; "
      << "++" << iter << ")";
  } else if (ttype->is_list()) {
    indent_h(out_h)
      << "for ("
      << "std::vector<" << type_name(((t_list*)ttype)->get_elem_type()) << " >::iterator "
      << iter  << "(" << prefix << ".begin()), "
      << "end" << "(" << prefix << ".end()); "
      << iter << " != end; "
      << "++" << iter << ")";
  }

  out_h << endl;
  indent_h.scope_up(out_h);

  if (ttype->is_map()) {
    generate_serialize_map_element(out_h, indent_h, (t_map*)ttype, iter, prefix);
  } else if (ttype->is_set()) {
    generate_serialize_set_element(out_h, indent_h, (t_set*)ttype, iter);
  } else if (ttype->is_list()) {
    generate_serialize_list_element(out_h, indent_h, (t_list*)ttype, iter);
  }

  if (ttype->is_map()) {
    indent_h(out_h) << "oprot.WriteMapEnd();" << endl;
  } else if (ttype->is_set()) {
    indent_h(out_h) << "oprot.WriteSetEnd();" << endl;
  } else if (ttype->is_list()) {
    indent_h(out_h) << "oprot.WriteListEnd();" << endl;
  }

  indent_h.scope_down(out_h);
  indent_h.scope_down(out_h);
}

void t_cppw_generator::generate_serialize_map_element(ofstream& out_h, t_indent& indent_h, t_map* tmap, string iter, string map) {
  t_field kfield(tmap->get_key_type(), iter + "->first");
  generate_serialize_field(out_h, indent_h, &kfield, "");
  t_field vfield(tmap->get_val_type(), iter + "->second");
  generate_serialize_field(out_h, indent_h, &vfield, "");
}

void t_cppw_generator::generate_serialize_set_element(ofstream& out_h, t_indent& indent_h, t_set* tset, string iter) {
  t_field efield(tset->get_elem_type(), "(*" + iter + ")");
  generate_serialize_field(out_h, indent_h, &efield, "");
}

void t_cppw_generator::generate_serialize_list_element(ofstream& out_h, t_indent& indent_h, t_list* tlist, string iter) {
  t_field efield(tlist->get_elem_type(), "(*" + iter + ")");
  generate_serialize_field(out_h, indent_h, &efield, "");
}

/**
 * Makes a :: prefix for a namespace.
 */
string t_cppw_generator::namespace_prefix(const vector<string> & ns) {
  string result;
  for (size_t i = 0; i != ns.size(); ++i)
  {
    result.append(ns.at(i));
    result.append("::");
  }
  return result;
}

/**
 * Makes given name unique by appending the program name.
 */
string t_cppw_generator::unique_name(string name) {
  stringstream stream;
  stream << name << " (" << program_name_ << ")";
  return stream.str();
}

bool t_cppw_generator::is_complex_type(t_type* ttype) {
  ttype = get_true_type(ttype);

  return
    ttype->is_container() ||
    ttype->is_struct() ||
    ttype->is_xception() ||
    (ttype->is_base_type() && (((t_base_type*)ttype)->get_base() == t_base_type::TYPE_STRING));
}

/**
 * Create, register, and initialize a new header file.
 */
void t_cppw_generator::create_header(string name, ofstream& out_h) {
  if (!namespaces_.empty())
    f_group_ << "#include \"" << namespaces_.back() << "/" << name << ".h\"" << endl;

  string path = namespace_dir_ + "/" + name +".h";
  out_h.open(path.c_str());

  out_h << "#pragma once" << endl << endl;
  out_h << autogen_comment() << endl;

  cppw_header_includes(out_h);
}

/**
 * Create a new implementation file.
 */
void t_cppw_generator::create_implementation(string name, ofstream& out_cpp) {
  string path = namespace_dir_ + "/" + unique_name(name) +".cpp";
  out_cpp.open(path.c_str());

  out_cpp << autogen_comment() << endl;
  out_cpp << "#include \"../" << namespaces_.back() << ".h\"" << endl;

  cppw_header_includes(out_cpp);

  using_namespace(out_cpp);
}

/**
 * Add a "using namespace" declaration.
 */
void t_cppw_generator::using_namespace(ofstream& out_cpp) {
  if (namespaces_.empty())
    return;
  out_cpp << "using namespace " << namespaces_.front();
  const size_t size = namespaces_.size();
  for (size_t i = 1; i != size; ++i)
    out_cpp << "::" << namespaces_.at(i);
  out_cpp << ";" << endl << endl;
}

/**
 * Split the namespace string by periods.
 */
void t_cppw_generator::parse_namespace(const string& ns, vector<string>& result) {
  string::size_type begin = 0;
  string::size_type end;
  for (;;)
  {
    end = ns.find('.', begin);
    if (end == string::npos)
      break;
    if (begin != end)
      result.push_back(ns.substr(begin, end - begin));
    begin = end + 1;
  }
  if (begin < ns.size())
    result.push_back(ns.substr(begin));
}

string t_cppw_generator::type_name(t_type* ttype, bool in_typedef, bool arg) {
  if (ttype->is_base_type()) {
    string bname = base_type_name(ttype);
    if (!arg) {
      return bname;
    }

    if (((t_base_type*)ttype)->get_base() == t_base_type::TYPE_STRING) {
      return "const " + bname + "&";
    } else {
      return "const " + bname;
    }
  }

  // Check for a custom overloaded C++ name
  if (ttype->is_container()) {
    string cname;

    t_container* tcontainer = (t_container*) ttype;
    if (tcontainer->has_cpp_name()) {
      cname = tcontainer->get_cpp_name();
    } else if (ttype->is_map()) {
      t_map* tmap = (t_map*) ttype;
      cname = "std::map<" +
        type_name(tmap->get_key_type(), in_typedef) + ", " +
        type_name(tmap->get_val_type(), in_typedef) + " >";
    } else if (ttype->is_set()) {
      t_set* tset = (t_set*) ttype;
      cname = "std::set<" + type_name(tset->get_elem_type(), in_typedef) + " >";
    } else if (ttype->is_list()) {
      t_list* tlist = (t_list*) ttype;
      cname = "std::vector<" + type_name(tlist->get_elem_type(), in_typedef) + " >";
    }

    if (arg) {
      return "const " + cname + "&";
    } else {
      return cname;
    }
  }

  string class_prefix;
  if (in_typedef && (ttype->is_struct() || ttype->is_xception())) {
    class_prefix = "class ";
  }

  // Check if it needs to be namespaced
  string pname;
  t_program* program = ttype->get_program();
  if (program != NULL && program != program_) {
    vector<string> ns;
    parse_namespace(program->get_namespace("cppw"), ns);
    pname =
      class_prefix +
      namespace_prefix(ns) +
      ttype->get_name();
  } else {
    pname = class_prefix + ttype->get_name();
  }

  if (arg) {
    if (is_complex_type(ttype)) {
      return "const " + pname + "&";
    } else {
      return "const " + pname;
    }
  } else {
    return pname;
  }
}

/**
 * Returns the C++ type that corresponds to the thrift type.
 *
 * @param tbase The base type
 * @return Explicit C++ type, i.e. "int32_t"
 */
string t_cppw_generator::base_type_name(t_type* type) {
  t_base_type::t_base tbase = ((t_base_type*)type)->get_base();
  switch (tbase) {
  case t_base_type::TYPE_VOID:
    return "void";
  case t_base_type::TYPE_STRING:
    if (((t_base_type*)type)->is_binary())
      return "Thrift::Protocol::TBinary";
    else
      return "Thrift::Protocol::TString";
  case t_base_type::TYPE_BOOL:
    return "bool";
  case t_base_type::TYPE_BYTE:
    return "__int8";
  case t_base_type::TYPE_I16:
    return "__int16";
  case t_base_type::TYPE_I32:
    return "__int32";
  case t_base_type::TYPE_I64:
    return "__int64";
  case t_base_type::TYPE_DOUBLE:
    return "double";
  default:
    throw "compiler error: no C++ base type name for base type " + t_base_type::t_base_name(tbase);
  }
}

string t_cppw_generator::declare_field(t_field* tfield, bool init) {
  string result = type_name(tfield->get_type()) + " " + tfield->get_name();
  if (init) {
    t_type* ttype = tfield->get_type();
    while (ttype->is_typedef()) {
      ttype = ((t_typedef*)ttype)->get_type();
    }
    if (ttype->is_base_type() && tfield->get_value() != NULL) {
      ofstream dummy;
      t_indent   indent;
      result += " = " + render_const_value(dummy, indent, tfield->get_name(), ttype, tfield->get_value());
    } else if (ttype->is_base_type()) {
      t_base_type::t_base tbase = ((t_base_type*)ttype)->get_base();
      switch (tbase) {
        case t_base_type::TYPE_VOID:
          throw "NO T_VOID CONSTRUCT";
        case t_base_type::TYPE_STRING:
          break;
        case t_base_type::TYPE_BOOL:
          result += " = false";
          break;
        case t_base_type::TYPE_BYTE:
        case t_base_type::TYPE_I16:
        case t_base_type::TYPE_I32:
        case t_base_type::TYPE_I64:
          result += " = 0";
          break;
        case t_base_type::TYPE_DOUBLE:
          result += " = (double)0";
          break;
      }
    } else if (ttype->is_enum()) {
      result += " = (" + type_name(ttype, false, true) + ")0";
    }
  }
  return result + ";";
}

string t_cppw_generator::function_signature(t_function* tfunction, string parent) {
  stringstream stream;
  stream << type_name(tfunction->get_returntype()) << " ";
  if (!parent.empty())
    stream << parent << "::";
  stream << tfunction->get_name() << "(" << argument_list(tfunction->get_arglist()) << ")";
  return stream.str();
}

string t_cppw_generator::argument_list(t_struct* tstruct) {
  string result = "";
  const vector<t_field*>& fields = tstruct->get_members();
  vector<t_field*>::const_iterator f_iter;
  bool first = true;
  for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
    if (first) {
      first = false;
    } else {
      result += ", ";
    }
    result += type_name((*f_iter)->get_type()) + " " + (*f_iter)->get_name();
  }
  return result;
}

string t_cppw_generator::type_to_enum(t_type* type) {
  while (type->is_typedef()) {
    type = ((t_typedef*)type)->get_type();
  }

  if (type->is_base_type()) {
    t_base_type::t_base tbase = ((t_base_type*)type)->get_base();
    switch (tbase) {
      case t_base_type::TYPE_VOID:
        throw "NO T_VOID CONSTRUCT";
      case t_base_type::TYPE_STRING:
        return "Thrift::Protocol::TypeString";
      case t_base_type::TYPE_BOOL:
        return "Thrift::Protocol::TypeBool";
      case t_base_type::TYPE_BYTE:
        return "Thrift::Protocol::TypeByte";
      case t_base_type::TYPE_I16:
        return "Thrift::Protocol::TypeI16";
      case t_base_type::TYPE_I32:
        return "Thrift::Protocol::TypeI32";
      case t_base_type::TYPE_I64:
        return "Thrift::Protocol::TypeI64";
      case t_base_type::TYPE_DOUBLE:
        return "Thrift::Protocol::TypeDouble";
    }
  } else if (type->is_enum()) {
    return "Thrift::Protocol::TypeI32";
  } else if (type->is_struct() || type->is_xception()) {
    return "Thrift::Protocol::TypeStruct";
  } else if (type->is_map()) {
    return "Thrift::Protocol::TypeMap";
  } else if (type->is_set()) {
    return "Thrift::Protocol::TypeSet";
  } else if (type->is_list()) {
    return "Thrift::Protocol::TypeList";
  }

  throw "INVALID TYPE IN type_to_enum: " + type->get_name();
}


THRIFT_REGISTER_GENERATOR(cppw, "Windows C++", "");
