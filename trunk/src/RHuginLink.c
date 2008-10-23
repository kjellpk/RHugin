#include "RHugin.h"
#include "RHuginLink.h"

/* Global variables defined in RHugin.c */

extern SEXP RHugin_domain_tag;
extern SEXP RHugin_node_tag;
extern SEXP RHugin_table_tag;
extern SEXP RHugin_expression_tag;
extern SEXP RHugin_model_tag;
extern SEXP RHugin_junction_tree_tag;
extern SEXP RHugin_clique_tag;

extern SEXP RHUGIN_ERROR;

extern SEXP RHUGIN_CHANCE;
extern SEXP RHUGIN_UTILITY;
extern SEXP RHUGIN_DECISION;
extern SEXP RHUGIN_INSTANCE;

extern SEXP RHUGIN_DISCRETE;
extern SEXP RHUGIN_CONTINUOUS;

extern SEXP RHUGIN_LABELED;
extern SEXP RHUGIN_BOOLEAN;
extern SEXP RHUGIN_NUMBERED;
extern SEXP RHUGIN_INTERVAL;

extern SEXP RHUGIN_OPERATOR_ADD;
extern SEXP RHUGIN_OPERATOR_SUBTRACT;
extern SEXP RHUGIN_OPERATOR_MULTIPLY;
extern SEXP RHUGIN_OPERATOR_DIVIDE;
extern SEXP RHUGIN_OPERATOR_POWER;

extern SEXP RHUGIN_OPERATOR_NEGATE;

extern SEXP RHUGIN_OPERATOR_EQUALS;
extern SEXP RHUGIN_OPERATOR_LESS_THAN;
extern SEXP RHUGIN_OPERATOR_GREATER_THAN;
extern SEXP RHUGIN_OPERATOR_NOT_EQUALS;
extern SEXP RHUGIN_OPERATOR_LESS_THAN_OR_EQUALS;
extern SEXP RHUGIN_OPERATOR_GREATER_THAN_OR_EQUALS;

extern SEXP RHUGIN_OPERATOR_NORMAL;
extern SEXP RHUGIN_OPERATOR_LOGNORMAL;
extern SEXP RHUGIN_OPERATOR_BETA;
extern SEXP RHUGIN_OPERATOR_GAMMA;
extern SEXP RHUGIN_OPERATOR_EXPONENTIAL;
extern SEXP RHUGIN_OPERATOR_WEIBULL;
extern SEXP RHUGIN_OPERATOR_UNIFORM;
extern SEXP RHUGIN_OPERATOR_TRIANGULAR;
extern SEXP RHUGIN_OPERATOR_PERT;

extern SEXP RHUGIN_OPERATOR_BINOMIAL;
extern SEXP RHUGIN_OPERATOR_POISSON;
extern SEXP RHUGIN_OPERATOR_NEGATIVEBINOMIAL;
extern SEXP RHUGIN_OPERATOR_GEOMETRIC;
extern SEXP RHUGIN_OPERATOR_DISTRIBUTION;
extern SEXP RHUGIN_OPERATOR_NOISYOR;

extern SEXP RHUGIN_OPERATOR_TRUNCATE;

extern SEXP RHUGIN_OPERATOR_MIN;
extern SEXP RHUGIN_OPERATOR_MAX;

extern SEXP RHUGIN_OPERATOR_LOG;
extern SEXP RHUGIN_OPERATOR_LOG2;
extern SEXP RHUGIN_OPERATOR_LOG10;
extern SEXP RHUGIN_OPERATOR_EXP;
extern SEXP RHUGIN_OPERATOR_SIN;
extern SEXP RHUGIN_OPERATOR_COS;
extern SEXP RHUGIN_OPERATOR_TAN;
extern SEXP RHUGIN_OPERATOR_SINH;
extern SEXP RHUGIN_OPERATOR_COSH;
extern SEXP RHUGIN_OPERATOR_TANH;
extern SEXP RHUGIN_OPERATOR_SQRT;
extern SEXP RHUGIN_OPERATOR_ABS;

extern SEXP RHUGIN_OPERATOR_FLOOR;
extern SEXP RHUGIN_OPERATOR_CEIL;

extern SEXP RHUGIN_OPERATOR_MOD;

extern SEXP RHUGIN_OPERATOR_IF;
extern SEXP RHUGIN_OPERATOR_AND;
extern SEXP RHUGIN_OPERATOR_OR;
extern SEXP RHUGIN_OPERATOR_NOT;

extern SEXP RHUGIN_OPERATOR_LABEL;
extern SEXP RHUGIN_OPERATOR_NUMBER;
extern SEXP RHUGIN_OPERATOR_BOOLEAN;
extern SEXP RHUGIN_OPERATOR_NODE;

extern SEXP RHUGIN_OPERATOR_ERROR;

extern SEXP RHUGIN_TM_CLIQUE_SIZE;
extern SEXP RHUGIN_TM_CLIQUE_WEIGHT;
extern SEXP RHUGIN_TM_FILL_IN_SIZE;
extern SEXP RHUGIN_TM_FILL_IN_WEIGHT;
extern SEXP RHUGIN_TM_TOTAL_WEIGHT;

extern SEXP RHUGIN_EQUILIBRIUM_SUM;
extern SEXP RHUGIN_EQUILIBRIUM_MAX;

extern SEXP RHUGIN_MODE_NORMAL;
extern SEXP RHUGIN_MODE_FAST_RETRACTION;

extern SEXP RHUGIN_CONSTRAINT_NONE;
extern SEXP RHUGIN_CONSTRAINT_EDGE_REQUIRED;
extern SEXP RHUGIN_CONSTRAINT_EDGE_FORBIDDEN;
extern SEXP RHUGIN_CONSTRAINT_FORWARD_EDGE_REQUIRED;
extern SEXP RHUGIN_CONSTRAINT_BACKWARD_EDGE_REQUIRED;
extern SEXP RHUGIN_CONSTRAINT_FORWARD_EDGE_FORBIDDEN;
extern SEXP RHUGIN_CONSTRAINT_BACKWARD_EDGE_FORBIDDEN;


/*******************************************************************************
  * The Hugin API 
*******************************************************************************/

/* Section 1.6 Errors */

SEXP RHugin_error_code(void)
{
  SEXP ret = R_NilValue;
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_error_code();
  UNPROTECT(1);

  return ret;
}


/* Section 1.6.1 Handling errors */

SEXP RHugin_error_name(SEXP Scode)
{
  SEXP ret = R_NilValue;
  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_error_name(INTEGER(Scode)[0])));
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_error_description(SEXP Scode)
{
  SEXP ret = R_NilValue;
  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_error_description(INTEGER(Scode)[0])));
  UNPROTECT(1);

  return ret;
}


/* Section 1.7 Taking advantage of multiple processors */

SEXP RHugin_domain_set_concurrency_level(SEXP Sdomain, SEXP Slevel)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_set_concurrency_level(domain, (size_t) INTEGER(Slevel)[0]);
  UNPROTECT(1);

  return ret;
}
  

SEXP RHugin_domain_get_concurrency_level(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_concurrency_level(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_set_grain_size(SEXP Sdomain, SEXP Ssize)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_set_grain_size(domain, (size_t) INTEGER(Ssize)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_grain_size(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_grain_size(domain);
  UNPROTECT(1);

  return ret;
}



/* Section 2.2 Domains: Creation and deletion */

SEXP RHugin_new_domain(void)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = h_new_domain();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_delete);
  }

  return ret;
}


SEXP RHugin_domain_delete(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_delete(domain);
  R_ClearExternalPtr(ret);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_clone(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL, clonedDomain = NULL;

  domain = domainPointerFromSEXP(Sdomain);
  clonedDomain = h_domain_clone(domain);

  if(clonedDomain) {
    ret = R_MakeExternalPtr(clonedDomain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_delete);
  }

  return ret;
}


/* Section 2.3 Nodes: Creation and deletion */

SEXP RHugin_domain_new_node(SEXP Sdomain, SEXP Scategory, SEXP Skind)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t newNode = NULL;
  h_node_category_t category;
  h_node_kind_t kind;

  domain = domainPointerFromSEXP(Sdomain);

  if(asChar(Scategory) == RHUGIN_CHANCE)
    category = h_category_chance;
  else if(asChar(Scategory) == RHUGIN_UTILITY)
    category = h_category_utility;
  else if(asChar(Scategory) == RHUGIN_DECISION)
    category = h_category_decision;
  else if(asChar(Scategory) == RHUGIN_INSTANCE)
    category = h_category_instance;
  else
    category = h_category_error;

  if(asChar(Skind) == RHUGIN_DISCRETE)
    kind = h_kind_discrete;
  else if(asChar(Skind) == RHUGIN_CONTINUOUS)
    kind = h_kind_continuous;
  else
    kind = h_kind_error;

  newNode = h_domain_new_node(domain, category, kind);

  if(newNode)
    ret = R_MakeExternalPtr(newNode, RHugin_node_tag, R_NilValue);

  return ret;
}


// SEXP RHugin_node_get_domain(SEXP Snode)


SEXP RHugin_node_get_category(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_category_t category = h_category_error;

  node = nodePointerFromSEXP(Snode);
  category = h_node_get_category(node);

  PROTECT(ret = allocVector(STRSXP, 1));

  switch(category) {
    case h_category_chance:
      SET_STRING_ELT(ret, 0, RHUGIN_CHANCE);
      break;

    case h_category_utility:
      SET_STRING_ELT(ret, 0, RHUGIN_UTILITY);
      break;

    case h_category_decision:
      SET_STRING_ELT(ret, 0, RHUGIN_DECISION);
      break;

    case h_category_instance:
      SET_STRING_ELT(ret, 0, RHUGIN_INSTANCE);
      break;

    case h_category_error:
      SET_STRING_ELT(ret, 0, RHUGIN_ERROR);
      break;
  }

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_get_kind(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_kind_t kind = h_kind_error;

  node = nodePointerFromSEXP(Snode);
  kind = h_node_get_kind(node);

  PROTECT(ret = allocVector(STRSXP, 1));

  switch(kind) {
    case h_kind_continuous:
      SET_STRING_ELT(ret, 0, RHUGIN_CONTINUOUS);
      break;

    case h_kind_discrete:
      SET_STRING_ELT(ret, 0, RHUGIN_DISCRETE);
      break;

    case h_kind_error:
      SET_STRING_ELT(ret, 0, RHUGIN_ERROR);
      break;
  }

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_delete(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_delete(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_clone(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t newNode = NULL;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);
  newNode = h_node_clone(node);

  if(newNode)
    ret = R_MakeExternalPtr(newNode, RHugin_node_tag, R_NilValue);

  return ret;
}


/* Section 2.4 The links of the network */

SEXP RHugin_node_add_parent(SEXP Schild, SEXP Sparent)
{
  SEXP ret = R_NilValue;
  h_node_t child = NULL, parent = NULL;
  h_status_t status;

  child = nodePointerFromSEXP(Schild);
  parent = nodePointerFromSEXP(Sparent);
  status = h_node_add_parent(child, parent);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_remove_parent(SEXP Snode, SEXP Sparent)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL, parent = NULL;
  h_status_t status;

  node = nodePointerFromSEXP(Snode);
  parent = nodePointerFromSEXP(Sparent);
  status = h_node_remove_parent(node, parent);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_switch_parent(SEXP Snode, SEXP Sold_parent, SEXP Snew_parent)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL, old_parent = NULL, new_parent = NULL;
  h_status_t status;

  node = nodePointerFromSEXP(Snode);
  old_parent = nodePointerFromSEXP(Sold_parent);
  new_parent = nodePointerFromSEXP(Snew_parent);
  status = h_node_switch_parent(node, old_parent, new_parent);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_reverse_edge(SEXP Snode1, SEXP Snode2)
{
  SEXP ret = R_NilValue;
  h_node_t node1 = NULL, node2 = NULL;
  h_status_t status;

  node1 = nodePointerFromSEXP(Snode1);
  node2 = nodePointerFromSEXP(Snode2);
  status = h_node_reverse_edge(node1, node2);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);  

  return ret;
}


SEXP RHugin_node_get_parents(SEXP Snode)
{
  SEXP ret = R_NilValue, dimnames = R_NilValue;
  h_node_t node = NULL;
  h_node_t *parents = NULL, *parent = NULL;
  int i = 0, n = 0;

  node = nodePointerFromSEXP(Snode);
  parents = h_node_get_parents(node);

  for(parent = parents; *parent != NULL; parent++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(dimnames = allocVector(STRSXP, n));
    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(parents[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(dimnames, i, mkChar( (char*) h_node_get_name(parents[i])));
    }
    setAttrib(ret, R_NamesSymbol, dimnames);

    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_node_get_children(SEXP Snode)
{
  SEXP ret = R_NilValue, dimnames = R_NilValue;
  h_node_t node = NULL;
  h_node_t *children = NULL, *child = NULL;
  int i = 0, n = 0;

  node = nodePointerFromSEXP(Snode);
  children = h_node_get_children(node);

  for(child = children; *child != NULL; child++)
    n++;

  PROTECT(ret = allocVector(VECSXP, n));
  PROTECT(dimnames = allocVector(STRSXP, n));
  for(i = 0; i < n; i++) {
    SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(children[i], RHugin_node_tag, R_NilValue));
    SET_STRING_ELT(dimnames, i, mkChar( (char*) h_node_get_name(children[i])));
  }
  setAttrib(ret, R_NamesSymbol, dimnames);

  UNPROTECT(2);
  return ret;
}


/* Section 2.5 The number of states of a node */

SEXP RHugin_node_set_number_of_states(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int states = 0;
  h_status_t status;

  node = nodePointerFromSEXP(Snode);
  states = INTEGER(Sstates)[0];
  status = h_node_set_number_of_states(node, states);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_number_of_states(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int states = 0;

  node = nodePointerFromSEXP(Snode);
  states = (int) h_node_get_number_of_states(node);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = states;
  UNPROTECT(1);

  return ret;
}


/* Section 2.6 The conditional probability and the utility table */

SEXP RHugin_node_get_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_table_t table = NULL;

  node = nodePointerFromSEXP(Snode);
  table = h_node_get_table(node);

  ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);
  return ret;
}


SEXP RHugin_node_touch_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status;

  node = nodePointerFromSEXP(Snode);
  status = h_node_touch_table(node);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_set_alpha(SEXP Snode, SEXP Salpha, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Salpha) == LENGTH(Si)) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Salpha)));

    for(i = 0; i < LENGTH(Salpha); i++)
      INTEGER(ret)[i] = (int) h_node_set_alpha(node, (h_double_t) REAL(Salpha)[i],
        (size_t) INTEGER(Si)[i]);

    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_set_beta(SEXP Snode, SEXP Sbeta, SEXP Sparent, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL, parent = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);
  parent = nodePointerFromSEXP(Sparent);

  if(LENGTH(Sbeta) == LENGTH(Si)) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Sbeta)));

    for(i = 0; i < LENGTH(Sbeta); i++)
      INTEGER(ret)[i] = (int) h_node_set_beta(node, (h_double_t) REAL(Sbeta)[i],
        parent, (size_t) INTEGER(Si)[i]);

    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_set_gamma(SEXP Snode, SEXP Sgamma, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Sgamma) == LENGTH(Si)) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Sgamma)));

    for(i = 0; i < LENGTH(Sgamma); i++)
      INTEGER(ret)[i] = (int) h_node_set_gamma(node, (h_double_t) REAL(Sgamma)[i],
        (size_t) INTEGER(Si)[i]);

    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_alpha(SEXP Snode, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0, n = -1;

  node = nodePointerFromSEXP(Snode);
  n = LENGTH(Si);

  if(n > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Si)));
    for(i = 0; i < n; i++)
      REAL(ret)[i] = (double) h_node_get_alpha(node, (size_t) INTEGER(Si)[i]);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_beta(SEXP Snode, SEXP Sparent, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL, parent = NULL;
  int i = 0, n = -1;

  node = nodePointerFromSEXP(Snode);
  parent = nodePointerFromSEXP(Sparent);
  n = LENGTH(Si);

  if(n > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Si)));
    for(i = 0; i < n; i++)
      REAL(ret)[i] = (double) h_node_get_beta(node, parent, (size_t) INTEGER(Si)[i]);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_gamma(SEXP Snode, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0, n = -1;

  node = nodePointerFromSEXP(Snode);
  n = LENGTH(Si);

  if(n > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Si)));
    for(i = 0; i < n; i++)
      REAL(ret)[i] = (double) h_node_get_gamma(node, (size_t) INTEGER(Si)[i]);
    UNPROTECT(1);
  }

  return ret;
}


/* Section 2.7 The name of a node */

SEXP RHugin_node_set_name(SEXP Snode, SEXP Sname)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status;

  node = nodePointerFromSEXP(Snode);
  status = h_node_set_name(node, (h_string_t) CHAR(asChar(Sname)));

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_name(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_node_get_name(node)));
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_node_by_name(SEXP Sdomain, SEXP Sname)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t node = NULL;

  domain = domainPointerFromSEXP(Sdomain);
  node = h_domain_get_node_by_name(domain, (h_string_t) CHAR(asChar(Sname)));

  if(node)
    ret = R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue);

  return ret;
}


/* Section 2.8 Iterating through the nodes of a domain */

SEXP RHugin_domain_get_first_node(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t node = NULL;

  domain = domainPointerFromSEXP(Sdomain);
  node = h_domain_get_first_node(domain);

  if(node)
    ret = R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_get_next(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL, next = NULL;

  node = nodePointerFromSEXP(Snode);
  next = h_node_get_next(node);

  if(next)
    ret = R_MakeExternalPtr(next, RHugin_node_tag, R_NilValue);

  return ret;
}


/* Section 2.9 User data */

// SEXP RHugin_node_set_user_data(SEXP Snode, SEXP Sdata);
// SEXP RHugin_node_get_user_data(SEXP Snode);
// SEXP RHugin_domain_set_user_data(SEXP Sdomain, SEXP Sdata);
// SEXP RHugin_domain_get_user_data(SEXP Sdomain);
// SEXP RHugin_node_set_attribute(SEXP Snode, SEXP Skey, SEXP Svalue);
// SEXP RHugin_node_get_attribute(SEXP Snode, SEXP Skey);
// SEXP RHugin_domain_set_attribute(SEXP Sdomain, SEXP Skey, SEXP Svalue);
// SEXP RHugin_domain_get_attribute(SEXP Sdomain, SEXP Skey);
// SEXP RHugin_node_get_first_attribute(SEXP Snode);
// SEXP RHugin_domain_get_first_attribute(SEXP Sdomain);
// SEXP RHugin_attribute_get_next(SEXP Sattribute);
// SEXP RHugin_attribute_get_key(SEXP Sattribute);
// SEXP RHugin_attribute_get_value(SEXP Sattribute);


/* Section 2.10 HUGIN Knowledge Base files */

SEXP RHugin_domain_save_as_kb(SEXP Sdomain, SEXP Sfile_name, SEXP Spassword)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  if(Spassword == R_NilValue)
    INTEGER(ret)[0] = (int) h_domain_save_as_kb(domain, (h_string_t) CHAR(asChar(Sfile_name)), NULL);
  else
    INTEGER(ret)[0] = (int) h_domain_save_as_kb(domain, (h_string_t) CHAR(asChar(Sfile_name)),
                                                (h_string_t) CHAR(asChar(Spassword)));
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_kb_load_domain(SEXP Sfile_name, SEXP Spassword)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  if(Spassword == R_NilValue)
    domain = h_kb_load_domain((h_string_t) CHAR(asChar(Sfile_name)), NULL);
  else
    domain = h_kb_load_domain((h_string_t) CHAR(asChar(Sfile_name)),
                              (h_string_t) CHAR(asChar(Spassword)));

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_delete); 
  }

  return ret;
}


SEXP RHugin_table_get_nodes(SEXP Stable)
{
  SEXP ret = R_NilValue, dimnames = R_NilValue;
  h_table_t table = NULL;
  h_node_t *nodes = NULL, *node = NULL;
  int i = 0, n = 0;

  table = tablePointerFromSEXP(Stable);
  nodes = h_table_get_nodes(table);

  for(node = nodes; *node != NULL; node++)
    n++;

  PROTECT(ret = allocVector(VECSXP, n));
  PROTECT(dimnames = allocVector(STRSXP, n));
  for(i = 0; i < n; i++) {
    SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(nodes[i], RHugin_node_tag, R_NilValue));
    SET_STRING_ELT(dimnames, i, mkChar( (char*) h_node_get_name(nodes[i])));
  }
  setAttrib(ret, R_NamesSymbol, dimnames);

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_table_get_data(SEXP Stable)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  double *data = NULL;
  int size = -1, IONE = 1;

  table = tablePointerFromSEXP(Stable);
  data = (double*) h_table_get_data(table);
  size = (int) h_table_get_size(table);

  if(size > 0) {
    PROTECT(ret = allocVector(REALSXP, size));
    F77_CALL(dcopy)(&size, data, &IONE, REAL(ret), &IONE);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_table_set_data(SEXP Stable, SEXP Sdata)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  double *data = NULL;
  int size = -1, IONE = 1;

  table = tablePointerFromSEXP(Stable);
  data = (double*) h_table_get_data(table);
  size = (int) h_table_get_size(table);

  if(size == LENGTH(Sdata))
    F77_CALL(dcopy)(&size, REAL(Sdata), &IONE, data, &IONE);
  else
    error("the length of Sdata is not equal to the length of the table data");

  return ret;
}


SEXP RHugin_table_get_mean(SEXP Stable, SEXP Si, SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_table_t table = NULL;
  int i = 0, n = -1;

  node = nodePointerFromSEXP(Snode);
  table = tablePointerFromSEXP(Stable);
  n = LENGTH(Si);

  if(n > 0) {
    PROTECT(ret = allocVector(REALSXP, n));
    for(i = 0; i < n; i++)
      REAL(ret)[i] = h_table_get_mean(table, (size_t) INTEGER(Si)[i], node);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_table_get_covariance(SEXP Stable, SEXP Si, SEXP Snode1, SEXP Snode2)
{
  SEXP ret = R_NilValue;
  h_node_t node1 = NULL, node2 = NULL;
  h_table_t table = NULL;
  int i = 0, n = -1;

  node1 = nodePointerFromSEXP(Snode1);
  node2 = nodePointerFromSEXP(Snode2);
  table = tablePointerFromSEXP(Stable);
  n = LENGTH(Si);

  if(n > 0) {
    PROTECT(ret = allocVector(REALSXP, n));
    for(i = 0; i < n; i++)
      REAL(ret)[i] = h_table_get_covariance(table, (size_t) INTEGER(Si)[i],
                                            node1, node2);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_table_get_variance(SEXP Stable, SEXP Si, SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_table_t table = NULL;
  int i = 0, n = -1;

  node = nodePointerFromSEXP(Snode);
  table = tablePointerFromSEXP(Stable);
  n = LENGTH(Si);

  if(n > 0) {
    PROTECT(ret = allocVector(REALSXP, n));
    for(i = 0; i < n; i++)
      REAL(ret)[i] = h_table_get_variance(table, (size_t) INTEGER(Si)[i], node);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_table_delete(SEXP Stable)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  h_status_t status;

  table = tablePointerFromSEXP(Stable);
  status = h_table_delete(table);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_table_get_size(SEXP Stable)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  size_t size;

  table = tablePointerFromSEXP(Stable);
  size = h_table_get_size(table);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) size;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_table_reorder_nodes(SEXP Stable, SEXP Sorder)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  h_node_t *order = NULL;
  h_status_t status;
  int i = 0, n = 0;

  table = tablePointerFromSEXP(Stable);
  n = LENGTH(Sorder);

  if(n > 0) {
    order = (h_node_t*) R_alloc(n+1, sizeof(h_node_t*));
    for(i = 0; i < n; i++)
      order[i] = nodePointerFromSEXP(VECTOR_ELT(Sorder, i));
    order[n] = NULL;

    status = h_table_reorder_nodes(table, order);

    PROTECT(ret = allocVector(INTSXP, 1));
    INTEGER(ret)[0] = (int) status;
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_set_subtype(SEXP Snode, SEXP Ssubtype)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_subtype_t subtype = h_subtype_error;
  h_status_t status = (h_status_t) 0;

  node = nodePointerFromSEXP(Snode);
  subtype = h_node_get_subtype(node);

  if(asChar(Ssubtype) == RHUGIN_LABELED)
    subtype = h_subtype_label;
  else if(asChar(Ssubtype) == RHUGIN_NUMBERED)
    subtype = h_subtype_number;
  else if(asChar(Ssubtype) == RHUGIN_BOOLEAN)
    subtype = h_subtype_boolean;
  else if(asChar(Ssubtype) == RHUGIN_INTERVAL)
    subtype = h_subtype_interval;
  else
    subtype = h_subtype_error;

  status = h_node_set_subtype(node, subtype);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_subtype(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_subtype_t subtype;

  node = nodePointerFromSEXP(Snode);
  subtype = h_node_get_subtype(node);

  PROTECT(ret = allocVector(STRSXP, 1));

  switch(subtype) {
    case h_subtype_label:
      SET_STRING_ELT(ret, 0, mkChar("labeled"));
      break;

    case h_subtype_error:
      SET_STRING_ELT(ret, 0, mkChar("error"));
      break;

    case h_subtype_number:
      SET_STRING_ELT(ret, 0, mkChar("numbered"));
      break;

    case h_subtype_boolean:
      SET_STRING_ELT(ret, 0, mkChar("boolean"));
      break;

    case h_subtype_interval:
      SET_STRING_ELT(ret, 0, mkChar("interval"));
      break;
  }

  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_make_expression(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_expression_t expression;

  node = nodePointerFromSEXP(Snode);
  expression = h_node_make_expression(node);

  if(expression) {
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_expression_delete);
  }

  return ret;
}


SEXP RHugin_label_make_expression(SEXP Slabel)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;

  expression = h_label_make_expression((h_string_t) CHAR(asChar(Slabel)));

  if(expression) {
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_expression_delete);
  }

  return ret;
}


SEXP RHugin_boolean_make_expression(SEXP Sboolean)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;

  expression = h_boolean_make_expression((h_boolean_t) LOGICAL(Sboolean)[0]);

  if(expression) {
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_expression_delete);
  }

  return ret;
}


SEXP RHugin_number_make_expression(SEXP Snumber)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;

  expression = h_number_make_expression((h_double_t) REAL(Snumber)[0]);

  if(expression) {
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_expression_delete);
  }

  return ret;
}


SEXP RHugin_make_composite_expression(SEXP Soperator, SEXP Sarguments)
{
  SEXP ret = R_NilValue;
  h_operator_t operator = h_operator_error;
  h_expression_t* arguments = NULL;
  h_expression_t expression = NULL;
  int i = 0, n = -1;

  if(asChar(Soperator) == RHUGIN_OPERATOR_ADD)
    operator = h_operator_add;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_SUBTRACT)
    operator = h_operator_subtract;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_MULTIPLY)
    operator = h_operator_multiply;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_DIVIDE)
    operator = h_operator_divide;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_POWER)
    operator = h_operator_power;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_NEGATE)
    operator = h_operator_negate;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_EQUALS)
    operator = h_operator_equals;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_LESS_THAN)
    operator = h_operator_less_than;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_GREATER_THAN)
    operator = h_operator_greater_than;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_NOT_EQUALS)
    operator = h_operator_not_equals;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_LESS_THAN_OR_EQUALS)
    operator = h_operator_less_than_or_equals;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_GREATER_THAN_OR_EQUALS)
    operator = h_operator_greater_than_or_equals;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_NORMAL)
    operator = h_operator_Normal;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_LOGNORMAL)
    operator = h_operator_LogNormal;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_BETA)
    operator = h_operator_Beta;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_GAMMA)
    operator = h_operator_Gamma;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_EXPONENTIAL)
    operator = h_operator_Exponential;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_WEIBULL)
    operator = h_operator_Weibull;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_UNIFORM)
    operator = h_operator_Uniform;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_TRIANGULAR)
    operator = h_operator_Triangular;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_PERT)
    operator = h_operator_PERT;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_BINOMIAL)
    operator = h_operator_Binomial;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_POISSON)
    operator = h_operator_Poisson;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_NEGATIVEBINOMIAL)
    operator = h_operator_NegativeBinomial;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_GEOMETRIC)
    operator = h_operator_Geometric;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_DISTRIBUTION)
    operator = h_operator_Distribution;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_NOISYOR)
    operator = h_operator_NoisyOR;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_TRUNCATE)
    operator = h_operator_truncate;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_MIN)
    operator = h_operator_min;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_MAX)
    operator = h_operator_max;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_LOG)
    operator = h_operator_log;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_LOG2)
    operator = h_operator_log2;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_LOG10)
    operator = h_operator_log10;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_EXP)
    operator = h_operator_exp;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_SIN)
    operator = h_operator_sin;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_COS)
    operator = h_operator_cos;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_TAN)
    operator = h_operator_tan;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_SINH)
    operator = h_operator_sinh;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_COSH)
    operator = h_operator_cosh;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_TANH)
    operator = h_operator_tanh;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_SQRT)
    operator = h_operator_sqrt;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_ABS)
    operator = h_operator_abs;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_FLOOR)
    operator = h_operator_floor;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_CEIL)
    operator = h_operator_ceil;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_MOD)
    operator = h_operator_mod;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_IF)
    operator = h_operator_if;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_AND)
    operator = h_operator_and;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_OR)
    operator = h_operator_or;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_NOT)
    operator = h_operator_not;

  else if(asChar(Soperator) == RHUGIN_OPERATOR_LABEL)
    operator = h_operator_label;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_NUMBER)
    operator = h_operator_number;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_BOOLEAN)
    operator = h_operator_boolean;
  else if(asChar(Soperator) == RHUGIN_OPERATOR_NODE)
    operator = h_operator_node;

  n = LENGTH(Sarguments);

  arguments = (h_expression_t*) R_alloc(n + 1, sizeof(h_expression_t*));
  for(i = 0; i < n; i++)
    arguments[i] = expressionPointerFromSEXP(VECTOR_ELT(Sarguments, i));
  arguments[n] = NULL;

  expression = h_make_composite_expression(operator, arguments);

  if(expression) {
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_expression_delete);
  }

  return ret;
}


SEXP RHugin_expression_is_composite(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;
  h_boolean_t composite;

  expression = expressionPointerFromSEXP(Sexpression);
  composite = h_expression_is_composite(expression);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) composite;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_expression_get_operator(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;
  h_operator_t operator;

  expression = expressionPointerFromSEXP(Sexpression);
  operator = h_expression_get_operator(expression);

  PROTECT(ret = allocVector(STRSXP, 1));

  switch(operator) {
    case h_operator_add:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_ADD);
      break;

    case h_operator_subtract:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_SUBTRACT);
      break;

    case h_operator_multiply:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_MULTIPLY);
      break;

    case h_operator_divide:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_DIVIDE);
      break;

    case h_operator_power:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_POWER);
      break;

    case h_operator_negate:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NEGATE);
      break;

    case h_operator_equals:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_EQUALS);
      break;

    case h_operator_less_than:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_LESS_THAN);
      break;

    case h_operator_greater_than:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_GREATER_THAN);
      break;

    case h_operator_not_equals:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NOT_EQUALS);
      break;

    case h_operator_less_than_or_equals:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_LESS_THAN_OR_EQUALS);
      break;

    case h_operator_greater_than_or_equals:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_GREATER_THAN_OR_EQUALS);
      break;

    case h_operator_Normal:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NORMAL);
      break;

    case h_operator_LogNormal:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_LOGNORMAL);
      break;

    case h_operator_Beta:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_BETA);
      break;

    case h_operator_Gamma:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_GAMMA);
      break;

    case h_operator_Exponential:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_EXPONENTIAL);
      break;

    case h_operator_Weibull:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_WEIBULL);
      break;

    case h_operator_Uniform:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_UNIFORM);
      break;

    case h_operator_Triangular:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_TRIANGULAR);
      break;

    case h_operator_PERT:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_PERT);
      break;

    case h_operator_Poisson:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_POISSON);
      break;

    case h_operator_NoisyOR:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NOISYOR);
      break;

    case h_operator_Binomial:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_BINOMIAL);
      break;

    case h_operator_Geometric:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_GEOMETRIC);
      break;

    case h_operator_Distribution:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_DISTRIBUTION);
      break;

    case h_operator_NegativeBinomial:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NEGATIVEBINOMIAL);
      break;

    case h_operator_truncate:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_TRUNCATE);
      break;

    case h_operator_min:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_MIN);
      break;

    case h_operator_max:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_MAX);
      break;

    case h_operator_log:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_LOG);
      break;

    case h_operator_log2:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_LOG2);
      break;

    case h_operator_log10:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_LOG10);
      break;

    case h_operator_exp:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_EXP);
      break;

    case h_operator_sin:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_SIN);
      break;

    case h_operator_cos:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_COS);
      break;

    case h_operator_tan:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_TAN);
      break;

    case h_operator_sinh:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_SINH);
      break;

    case h_operator_cosh:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_COSH);
      break;

    case h_operator_tanh:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_TANH);
      break;

    case h_operator_sqrt:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_SQRT);
      break;

    case h_operator_abs:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_ABS);
      break;

    case h_operator_floor:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_FLOOR);
      break;

    case h_operator_ceil:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_CEIL);
      break;

    case h_operator_mod:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_MOD);
      break;

    case h_operator_if:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_IF);
      break;

    case h_operator_and:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_AND);
      break;

    case h_operator_or:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_OR);
      break;

    case h_operator_not:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NOT);
      break;

    case h_operator_label:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_LABEL);
      break;

    case h_operator_number:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NUMBER);
      break;

    case h_operator_boolean:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_BOOLEAN);
      break;

    case h_operator_node:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_NODE);
      break;

    default:
      SET_STRING_ELT(ret, 0, RHUGIN_OPERATOR_ERROR);
      break;
  }

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_expression_get_operands(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;
  h_expression_t *operand, *operands;
  int i = 0, n = 0;
  
  expression = expressionPointerFromSEXP(Sexpression);
  operands = h_expression_get_operands(expression);

  for(operand = operands; *operand != NULL; operand++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    for(i = 0; i < n; i++)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(operands[i], RHugin_expression_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_expression_get_node(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;
  h_node_t node = NULL;

  expression = expressionPointerFromSEXP(Sexpression);
  node = h_expression_get_node(expression);

  if(node)
    ret = R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue);

  return ret;
}

  
SEXP RHugin_expression_get_number(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;
  h_double_t number = 0.0;

  expression = expressionPointerFromSEXP(Sexpression);
  number = h_expression_get_number(expression);

  PROTECT(ret = allocVector(VECSXP, 1));
  REAL(ret)[0] = (double) number;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_expression_get_label(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression;

  expression = expressionPointerFromSEXP(Sexpression);

  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_expression_get_label(expression)));
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_expression_get_boolean(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression = NULL;
  h_boolean_t boolean = (h_boolean_t) 0;

  expression = expressionPointerFromSEXP(Sexpression);
  boolean = h_expression_get_boolean(expression);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) boolean;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_expression_clone(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression = NULL, clone = NULL;

  expression = expressionPointerFromSEXP(Sexpression);
  clone = h_expression_clone(expression);

  if(clone)
    ret = R_MakeExternalPtr(clone, RHugin_expression_tag, R_NilValue);

  return ret;
}


SEXP RHugin_expression_delete(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_expression_t expression = NULL;
  h_status_t status = -1;

  expression = expressionPointerFromSEXP(Sexpression);
  status = h_expression_delete(expression);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


/* Section 5.3 Syntax for expression */

// SEXP RHugin_string_parse_expression(SEXP Sstring, SEXP Smodel, SEXP Serror_handler, SEXP Sdata)
// SEXP RHugin_expression_tago_string(SEXP Sexpression)


/* Section 5.4 Creating and maintaining models */

SEXP RHugin_node_new_model(SEXP Snode, SEXP Smodel_nodes)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_t *model_nodes = NULL;
  h_model_t model = NULL;
  int i = 0, n = 0;

  node = nodePointerFromSEXP(Snode);
  n = LENGTH(Smodel_nodes);

  if(n > 0) {
    model_nodes = (h_node_t*) R_alloc(n+1, sizeof(h_node_t*));
    for(i = 0; i < n; i++)
      model_nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Smodel_nodes, i));
    model_nodes[n] = NULL;

    model = h_node_new_model(node, model_nodes);

    if(model)
      ret = R_MakeExternalPtr(model, RHugin_model_tag, R_NilValue);
  }

  return ret;
}


SEXP RHugin_node_get_model(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_model_t model = NULL;

  node = nodePointerFromSEXP(Snode);
  model = h_node_get_model(node);

  if(model)
    ret = R_MakeExternalPtr(model, RHugin_model_tag, R_NilValue);

  return ret;
}


SEXP RHugin_model_delete(SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_model_t model = NULL;
  h_status_t status = (h_status_t) 0;

  model = modelPointerFromSEXP(Smodel);
  status = h_model_delete(model);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_model_get_nodes(SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_model_t model = NULL;
  h_node_t *node = NULL, *nodes = NULL;
  int i = 0, n = 0;

  model = modelPointerFromSEXP(Smodel);
  nodes = h_model_get_nodes(model);

  for(node = nodes; *node != NULL; node++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    for(i = 0; i < n; i++)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(nodes[i], RHugin_node_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_model_get_size(SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_model_t model = NULL;
  size_t size = 0;

  model = modelPointerFromSEXP(Smodel);
  size = h_model_get_size(model);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) size;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_model_set_expression(SEXP Smodel, SEXP Sindex, SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_model_t model = NULL;
  size_t index = 0;
  h_expression_t expression = NULL;
  h_status_t status = (h_status_t) 0;

  model = modelPointerFromSEXP(Smodel);
  index = (size_t) INTEGER(Sindex)[0];
  expression = expressionPointerFromSEXP(Sexpression);

  status = h_model_set_expression(model, index, expression);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_model_get_expression(SEXP Smodel, SEXP Sindex)
{
  SEXP ret = R_NilValue;
  h_model_t model = NULL;
  size_t index = 0;
  h_expression_t expression = NULL;

  model = modelPointerFromSEXP(Smodel);
  index = (size_t) INTEGER(Sindex)[0];

  expression = h_model_get_expression(model, index);

  if(expression)
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);

  return ret;
}


/* Section 5.5 State labels */

SEXP RHugin_node_set_state_label(SEXP Snode, SEXP Ss, SEXP Slabel)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Ss) == LENGTH(Slabel)) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Ss)));

    for(i = 0; i < LENGTH(Ss); i++)
      INTEGER(ret)[i] = (int) h_node_set_state_label(node, (size_t) INTEGER(Ss)[i],
                              (h_string_t) CHAR(STRING_ELT(Slabel, i)));

    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_state_label(SEXP Snode, SEXP Ss)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Ss) > 0) {
    PROTECT(ret = allocVector(STRSXP, LENGTH(Ss)));

    for(i = 0; i < LENGTH(Ss); i++)
      SET_STRING_ELT(ret, i, mkChar( (char*) h_node_get_state_label(node, (size_t) INTEGER(Ss)[i])));

    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_state_index_from_label(SEXP Snode, SEXP Slabel)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Slabel) > 0) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Slabel)));

    for(i = 0; i < LENGTH(Slabel); i++)
      INTEGER(ret)[i] = (int) h_node_get_state_index_from_label(node, (h_string_t) CHAR(STRING_ELT(Slabel, i)));

    UNPROTECT(1);
  }

  return ret;
}


/* Section 5.6 State values */

SEXP RHugin_node_set_state_value(SEXP Snode, SEXP Ss, SEXP Svalue)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Svalue) > 0) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Svalue)));

    for(i = 0; i < LENGTH(Svalue); i++)
      INTEGER(ret)[i] = (int) h_node_set_state_value(node, (size_t) INTEGER(Ss)[i], (h_double_t) REAL(Svalue)[i]);

    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_state_value(SEXP Snode, SEXP Ss)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Ss) > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Ss)));

    for(i = 0; i < LENGTH(Ss); i++)
      REAL(ret)[i] = (double) h_node_get_state_value(node, (size_t) INTEGER(Ss)[i]);

    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_state_index_from_value(SEXP Snode, SEXP Svalue)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Svalue) > 0) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Svalue)));

    for(i = 0; i < LENGTH(Svalue); i++)
      INTEGER(ret)[i] = (int) h_node_get_state_index_from_value(node, (h_double_t) REAL(Svalue)[i]);

    UNPROTECT(1);
  }

  return ret;
}


/* Section 5.8 Generating tables */

SEXP RHugin_node_generate_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status = (h_status_t) 0;

  node = nodePointerFromSEXP(Snode);
  status = h_node_generate_table(node);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_generate_tables(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_status_t status = (h_status_t) 0;

  domain = domainPointerFromSEXP(Sdomain);
  status = h_domain_generate_tables(domain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


// SEXP RHugin_class_generate_tables(SEXP Sclass)
// SEXP RHugin_class_set_log_file(SEXP Sclass, SEXP Slog_file)


/* Section 5.9 How the computations are done */

SEXP RHugin_model_set_number_of_samples_per_interval(SEXP Smodel, SEXP Scount)
{
  SEXP ret = R_NilValue;
  h_model_t model = NULL;
  h_status_t status = (h_status_t) 0;

  model = modelPointerFromSEXP(Smodel);
  status = h_model_set_number_of_samples_per_interval(model, (size_t) INTEGER(Scount)[0]);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_model_get_number_of_samples_per_interval(SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_model_t model = NULL;
  h_count_t count = (h_count_t) 0;

  model = modelPointerFromSEXP(Smodel);
  count = h_model_get_number_of_samples_per_interval(model);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) count;
  UNPROTECT(1);

  return ret;
}


/* Section 6.2 Compilation */

SEXP RHugin_domain_compile(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_status_t status = (h_status_t) 0;

  domain = domainPointerFromSEXP(Sdomain);
  if(!h_domain_is_compiled(domain))
    status = h_domain_compile(domain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_is_compiled(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_boolean_t boolean = FALSE;

  domain = domainPointerFromSEXP(Sdomain);
  boolean = h_domain_is_compiled(domain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) boolean;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_set_max_number_of_separators(SEXP Sdomain, SEXP Scount)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_status_t status = (h_status_t) 0;

  domain = domainPointerFromSEXP(Sdomain);
  status = h_domain_set_max_number_of_separators(domain, (size_t) INTEGER(Scount)[0]);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_max_number_of_separators(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_max_number_of_separators(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_triangulate(SEXP Sdomain, SEXP Smethod)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_triangulation_method_t method = h_tm_fill_in_weight;
  h_status_t status = (h_status_t) 0;

  domain = domainPointerFromSEXP(Sdomain);

  if(asChar(Smethod) == RHUGIN_TM_CLIQUE_SIZE)
    method = h_tm_clique_size;
  else if(asChar(Smethod) == RHUGIN_TM_CLIQUE_WEIGHT)
    method = h_tm_fill_in_weight;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_SIZE)
    method = h_tm_clique_weight;
  else if(asChar(Smethod) == RHUGIN_TM_TOTAL_WEIGHT)
    method = h_tm_total_weight;

  status = h_domain_triangulate(domain, method);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_triangulate_with_order(SEXP Sdomain, SEXP Sorder)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_status_t status = (h_status_t) 0;
  h_node_t *order = NULL;
  int i = 0;

  domain = domainPointerFromSEXP(Sdomain);

  if(LENGTH(Sorder) > 0) {
    order = (h_node_t*) R_alloc(1 + LENGTH(Sorder), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Sorder); i++)
      order[i] = nodePointerFromSEXP(VECTOR_ELT(Sorder, i));
    order[LENGTH(Sorder)] = NULL;
  }

  status = h_domain_triangulate_with_order(domain, order);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_elimination_order(SEXP Sdomain)
{
  SEXP ret = R_NilValue, dimnames = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t *order = NULL, *pnode = NULL;
  int i = 0, n = 0;

  domain = domainPointerFromSEXP(Sdomain);
  order = h_domain_get_elimination_order(domain);

  for(pnode = order; *pnode != NULL; pnode++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(dimnames = allocVector(STRSXP, n));
    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(order[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(dimnames, i, mkChar( (char*) h_node_get_name(order[i])));
    }
    setAttrib(ret, R_NamesSymbol, dimnames);

    UNPROTECT(2);
  }

  return ret;
}


// SEXP RHugin_domain_parse_nodes(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata)
// SEXP RHugin_class_parse_nodes(SEXP Sclass, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata)


/* Section 6.4 Getting a compilation log */

// SEXP RHugin_domain_set_log_file(SEXP Sdomain, SEXP Slog_file)


/* Section 6.5 Uncompilation */

SEXP RHugin_domain_uncompile(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_status_t status = (h_status_t) 0;

  domain = domainPointerFromSEXP(Sdomain);
  status = h_domain_uncompile(domain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


/* Section 6.5 Compression */

SEXP RHugin_domain_compress(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_compress(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_is_compressed(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_boolean_t boolean = (h_boolean_t) 0;

  domain = domainPointerFromSEXP(Sdomain);
  boolean = h_domain_is_compressed(domain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) boolean;
  UNPROTECT(1);

  return ret;
}


/* Section 6.7 Approxiamtion */

SEXP RHugin_domain_approximate(SEXP Sdomain, SEXP Sepsilon)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);
  
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_approximate(domain, (h_double_t) REAL(Sepsilon)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_approximation_constant(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_approximation_constant(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 7.2 Junction trees */

SEXP RHugin_domain_get_first_junction_tree(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_junction_tree_t jt = NULL;

  domain = domainPointerFromSEXP(Sdomain);
  jt = h_domain_get_first_junction_tree(domain);

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_jt_get_next(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;

  jt = jtPointerFromSEXP(Sjt);
  jt = h_jt_get_next(jt);

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_clique_get_junction_tree(SEXP Sclique)
{
  SEXP ret = R_NilValue;
  h_clique_t clique = NULL;
  h_junction_tree_t jt = NULL;

  clique = cliquePointerFromSEXP(Sclique);
  jt = h_clique_get_junction_tree(clique);

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_get_junction_tree(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_junction_tree_t jt = NULL;

  node = nodePointerFromSEXP(Snode);
  jt = h_node_get_junction_tree(node);

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_jt_get_cliques(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_clique_t *clique = NULL, *cliques = NULL;
  int i = 0, n = 0;

  jt = jtPointerFromSEXP(Sjt);
  cliques = h_jt_get_cliques(jt);

  for(clique = cliques; *clique != NULL; clique++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    for(i = 0; i < n; i++)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(cliques[i], RHugin_clique_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_jt_get_root(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_clique_t clique = NULL;

  jt = jtPointerFromSEXP(Sjt);
  clique = h_jt_get_root(jt);

  if(clique)
    ret = R_MakeExternalPtr(clique, RHugin_clique_tag, R_NilValue);

  return ret;
}


/* Section 7.3 Cliques */

SEXP RHugin_clique_get_members(SEXP Sclique)
{
  SEXP ret = R_NilValue, dimnames = R_NilValue;
  h_clique_t clique = NULL;
  h_node_t *node = NULL, *nodes = NULL;
  int i = 0, n = 0;

  clique = cliquePointerFromSEXP(Sclique);
  nodes = h_clique_get_members(clique);

  for(node = nodes; *node != NULL; node++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(dimnames = allocVector(STRSXP, n));
    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(nodes[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(dimnames, i, mkChar( (char*) h_node_get_name(nodes[i])));
    }
    setAttrib(ret, R_NamesSymbol, dimnames);

    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_clique_get_neighbors(SEXP Sclique)
{
  SEXP ret = R_NilValue;
  h_clique_t clique = NULL;
  h_clique_t *neighbor = NULL, *neighbors = NULL;
  int i = 0, n = 0;

  clique = cliquePointerFromSEXP(Sclique);
  neighbors = h_clique_get_neighbors(clique);

  for(neighbor = neighbors; *neighbor != NULL; neighbor++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    for(i = 0; i < n; i++)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(neighbors[i], RHugin_clique_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


/* Section 8.2 Entering evidence */

SEXP RHugin_node_select_state(SEXP Snode, SEXP Sstate)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_select_state(node, (size_t) INTEGER(Sstate)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_enter_finding(SEXP Snode, SEXP Sstate, SEXP Svalue)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Sstate) == LENGTH(Svalue)) {
    PROTECT(ret = allocVector(INTSXP, LENGTH(Sstate)));
    for(i = 0; i < LENGTH(Sstate); i++)
      INTEGER(ret)[i] = (int) h_node_enter_finding(node, (size_t) INTEGER(Sstate)[i], (h_number_t) REAL(Svalue)[i]);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_enter_value(SEXP Snode, SEXP Svalue)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_enter_value(node, REAL(Svalue)[0]);
  UNPROTECT(1);

  return ret;
}


/* Section 8.3 Retracting evidence */

SEXP RHugin_node_retract_findings(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_retract_findings(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_retract_findings(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_retract_findings(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 8.4 Determining independence properties */

SEXP RHugin_domain_get_d_connected_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft)
{
  SEXP ret = R_NilValue, dimnames = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t *source = NULL, *hard = NULL, *soft = NULL, *d_connected = NULL, *node = NULL;
  int i = 0, n = 0;

  domain = domainPointerFromSEXP(Sdomain);

  if(LENGTH(Ssource) > 0) {
    source = (h_node_t*) R_alloc(1 + LENGTH(Ssource), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Ssource); i++)
      source[i] = nodePointerFromSEXP(VECTOR_ELT(Ssource, i));
    source[LENGTH(Ssource)] = NULL;
  }

  if(LENGTH(Shard) > 0) {
    hard = (h_node_t*) R_alloc(1 + LENGTH(Shard), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Shard); i++)
      hard[i] = nodePointerFromSEXP(VECTOR_ELT(Shard, i));
    hard[LENGTH(Shard)] = NULL;
  }

  if(LENGTH(Ssoft) > 0) {
    soft = (h_node_t*) R_alloc(1 + LENGTH(Ssoft), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Ssoft); i++)
      soft[i] = nodePointerFromSEXP(VECTOR_ELT(Ssoft, i));
    soft[LENGTH(Ssoft)] = NULL;
  }

  d_connected = h_domain_get_d_connected_nodes(domain, source, hard, soft);

  for(node = d_connected; *node != NULL; node++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(dimnames = allocVector(STRSXP, n));
    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(d_connected[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(dimnames, i, mkChar( (char*) h_node_get_name(d_connected[i])));
    }
    setAttrib(ret, R_NamesSymbol, dimnames);

    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_domain_get_d_separated_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft)
{
  SEXP ret = R_NilValue, dimnames = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t *source = NULL, *hard = NULL, *soft = NULL, *d_separated = NULL, *node = NULL;
  int i = 0, n = 0;

  domain = domainPointerFromSEXP(Sdomain);

  if(LENGTH(Ssource) > 0) {
    source = (h_node_t*) R_alloc(1 + LENGTH(Ssource), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Ssource); i++)
      source[i] = nodePointerFromSEXP(VECTOR_ELT(Ssource, i));
    source[LENGTH(Ssource)] = NULL;
  }

  if(LENGTH(Shard) > 0) {
    hard = (h_node_t*) R_alloc(1 + LENGTH(Shard), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Shard); i++)
      hard[i] = nodePointerFromSEXP(VECTOR_ELT(Shard, i));
    hard[LENGTH(Shard)] = NULL;
  }

  if(LENGTH(Ssoft) > 0) {
    soft = (h_node_t*) R_alloc(1 + LENGTH(Ssoft), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Ssoft); i++)
      soft[i] = nodePointerFromSEXP(VECTOR_ELT(Ssoft, i));
    soft[LENGTH(Ssoft)] = NULL;
  }

  d_separated = h_domain_get_d_connected_nodes(domain, source, hard, soft);

  for(node = d_separated; *node != NULL; node++)
    n++;

  if(n > 0) {
    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(dimnames = allocVector(STRSXP, n));
    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(d_separated[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(dimnames, i, mkChar( (char*) h_node_get_name(d_separated[i])));
    }
    setAttrib(ret, R_NamesSymbol, dimnames);
    UNPROTECT(2);
  }

  return ret;
}


/* Section 8.5 Retreiving beliefs */

SEXP RHugin_node_get_belief(SEXP Snode, SEXP Sstate)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Sstate) > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Sstate)));
    for(i = 0; i < LENGTH(Sstate); i++)
      REAL(ret)[i] = (double) h_node_get_belief(node, (size_t) INTEGER(Sstate)[i]);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_mean(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_mean(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_variance(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_variance(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_marginal(SEXP Sdomain, SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t *nodes = NULL;
  h_table_t table = NULL;
  int i = 0;

  domain = domainPointerFromSEXP(Sdomain);

  if(LENGTH(Snodes) > 0) {
    nodes = (h_node_t*) R_alloc(1 + LENGTH(Snodes), sizeof(h_node_t*));
    for(i = 0; i < LENGTH(Snodes); i++)
      nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    nodes[LENGTH(Snodes)] = NULL;
  }

  table = h_domain_get_marginal(domain, nodes);

  if(table)
     ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_get_distribution(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_table_t table = NULL;

  node = nodePointerFromSEXP(Snode);
  table = h_node_get_distribution(node);

  if(table)
     ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


/* Section 8.6 Retrieving expected utilities */

SEXP RHugin_node_get_expected_utility(SEXP Snode, SEXP Sstate)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Sstate) > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Sstate)));
    for(i = 0; i < LENGTH(Sstate); i++)
      REAL(ret)[0] = (double) h_node_get_expected_utility(node, (size_t) INTEGER(Sstate)[i]);
    UNPROTECT(1);
  }

  return ret;
}


/* Section 8.7 Examining Evidence */

SEXP RHugin_node_get_entered_finding(SEXP Snode, SEXP Sstate)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Sstate) > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Sstate)));
    for(i = 0; i < LENGTH(Sstate); i++)
      REAL(ret)[i] = (double) h_node_get_entered_finding(node, (size_t) INTEGER(Sstate)[i]);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_propagated_finding(SEXP Snode, SEXP Sstate)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  if(LENGTH(Sstate) > 0) {
    PROTECT(ret = allocVector(REALSXP, LENGTH(Sstate)));
    for(i = 0; i < LENGTH(Sstate); i++)
      REAL(ret)[0] = (double) h_node_get_propagated_finding(node, (size_t) INTEGER(Sstate)[i]);
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_entered_value(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_entered_value(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_propagated_value(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_propagated_value(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_evidence_is_entered(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_evidence_is_entered(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_likelihood_is_entered(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_likelihood_is_entered(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_evidence_is_propagated(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_evidence_is_propagated(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_likelihood_is_propagated(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_likelihood_is_propagated(node);
  UNPROTECT(1);

  return ret;
}


/* Section 8.8 Case files */

SEXP RHugin_domain_save_case(SEXP Sdomain, SEXP Sfile_name)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_save_case(domain, (h_string_t) CHAR(asChar(Sfile_name)));
  UNPROTECT(1);

  return ret;
}


// SEXP RHugin_domain_parse_case(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_handler, SEXP Sdata)


/* Section 9.2 Propagation */

SEXP RHugin_domain_propagate(SEXP Sdomain, SEXP Sequilibrium, SEXP Smode)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_equilibrium_t equilibrium = h_equilibrium_sum;
  h_evidence_mode_t mode = h_mode_normal;

  domain = domainPointerFromSEXP(Sdomain);

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_propagate(domain, equilibrium, mode);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_propagate(SEXP Sjt, SEXP Sequilibrium, SEXP Smode)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_equilibrium_t equilibrium = h_equilibrium_sum;
  h_evidence_mode_t mode = h_mode_normal;

  jt = jtPointerFromSEXP(Sjt);

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_jt_propagate(jt, equilibrium, mode);
  UNPROTECT(1);

  return ret;
}


/* Section 9.3 Conflict of evidence */

SEXP RHugin_domain_get_conflict(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_conflict(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_get_conflict(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;

  jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_jt_get_conflict(jt);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_reset_inference_engine(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_reset_inference_engine(domain);
  UNPROTECT(1);

  return ret;
}


/* Secttion 9.4 The normalization constant */

SEXP RHugin_domain_get_normalization_constant(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_normalization_constant(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_log_normalization_constant(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_log_normalization_constant(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 9.5 Initializing the domain */

SEXP RHugin_domain_save_to_memory(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_save_to_memory(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_initialize(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_initialize(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 9.6 Querying the state of the inference engine */

SEXP RHugin_domain_equilibrium_is(SEXP Sdomain, SEXP Sequilibrium)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_equilibrium_t equilibrium = h_equilibrium_sum;

  domain = domainPointerFromSEXP(Sdomain);

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_equilibrium_is(domain, equilibrium);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_equilibrium_is(SEXP Sjt, SEXP Sequilibrium)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_equilibrium_t equilibrium = h_equilibrium_sum;

  jt = jtPointerFromSEXP(Sjt);

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_equilibrium_is(jt, equilibrium);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_evidence_mode_is(SEXP Sdomain, SEXP Smode)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_evidence_mode_t mode = h_mode_normal;

  domain = domainPointerFromSEXP(Sdomain);

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_evidence_mode_is(domain, mode);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_evidence_mode_is(SEXP Sjt, SEXP Smode)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_evidence_mode_t mode = h_mode_normal;

  jt = jtPointerFromSEXP(Sjt);

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_evidence_mode_is(jt, mode);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_evidence_is_propagated(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_evidence_is_propagated(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_evidence_is_propagated(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;

  jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_evidence_is_propagated(jt);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_likelihood_is_propagated(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_likelihood_is_propagated(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_likelihood_is_propagated(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;

  jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_likelihood_is_propagated(jt);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_cg_evidence_is_propagated(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_cg_evidence_is_propagated(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_cg_evidence_is_propagated(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;

  jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_cg_evidence_is_propagated(jt);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_evidence_to_propagate(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_evidence_to_propagate(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_evidence_to_propagate(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;

  jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_evidence_to_propagate(jt);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_evidence_to_propagate(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_evidence_to_propagate(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_tables_to_propagate(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_tables_to_propagate(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_tables_to_propagate(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;

  jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_tables_to_propagate(jt);
  UNPROTECT(1);

  return ret;
}


/* Section 9.7 Simulation */

SEXP RHugin_domain_simulate(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_simulate(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_sampled_state(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_get_sampled_state(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_sampled_value(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_sampled_value(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_seed_random(SEXP Sdomain, SEXP Sseed)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_seed_random(domain, (unsigned int) INTEGER(Sseed)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_uniform_deviate(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_uniform_deviate(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_normal_deviate(SEXP Sdomain, SEXP Smean, SEXP Svariance)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_normal_deviate(domain, REAL(Smean)[0], REAL(Svariance)[0]);
  UNPROTECT(1);

  return ret;
}


/* Section 9.8 Value of information analysis */

SEXP RHugin_node_get_entropy(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_entropy(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_mutual_information(SEXP Snode, SEXP Sother)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL, other = NULL;

  node = nodePointerFromSEXP(Snode);
  other = nodePointerFromSEXP(Sother);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_mutual_information(node, other);
  UNPROTECT(1);

  return ret;
}


/* Section 10.1 Experience counts and fading factors */

SEXP RHugin_node_get_experience_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_table_t table = NULL;

  node = nodePointerFromSEXP(Snode);
  table = h_node_get_experience_table(node);

  if(table)
    ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_has_experience_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_has_experience_table(node);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_fading_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_table_t table = NULL;

  node = nodePointerFromSEXP(Snode);
  table = h_node_get_fading_table(node);

  if(table)
    ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_has_fading_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_has_fading_table(node);
  UNPROTECT(1);

  return ret;
}


/* Section 10.2 Updating tables */

SEXP RHugin_domain_adapt(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_adapt(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 11.1 Data */

SEXP RHugin_domain_set_number_of_cases(SEXP Sdomain, SEXP Scount)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_set_number_of_cases(domain, (size_t) INTEGER(Scount)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_new_case(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_new_case(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_number_of_cases(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_number_of_cases(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_set_case_state(SEXP Snode, SEXP Scase_index, SEXP Sstate)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status = (h_status_t) 0;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = 0;

  for(i = 0; i < LENGTH(Scase_index); i++) {
    status = h_node_set_case_state(node, (size_t) INTEGER(Scase_index)[i],
                                   (size_t) INTEGER(Sstate)[i]);

    if(status != 0) {
      INTEGER(ret)[0] = (int) status;
      UNPROTECT(1);
      return ret;
    }
  }

  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_case_state(SEXP Snode, SEXP Scase_index)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, LENGTH(Scase_index)));
  for(i = 0; i < LENGTH(Scase_index); i++) {
    INTEGER(ret)[i] = h_node_case_is_set(node, (size_t) INTEGER(Scase_index)[i]) ?
                      (int) h_node_get_case_state(node, (size_t) INTEGER(Scase_index)[i]) :
                      NA_INTEGER;
  }

  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_set_case_value(SEXP Snode, SEXP Scase_index, SEXP Svalue)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status = (h_status_t) 0;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = 0;

  for(i = 0; i < LENGTH(Scase_index); i++) {
    if(ISNA(REAL(Svalue)[i]))
      status = h_node_unset_case(node, (size_t) INTEGER(Scase_index)[i]);
    else
      status = h_node_set_case_value(node, (size_t) INTEGER(Scase_index)[i], REAL(Svalue)[i]);

    if(status != 0) {
      INTEGER(ret)[0] = (int) status;
      UNPROTECT(1);
      return ret;
    }
  }
  
  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_get_case_value(SEXP Snode, SEXP Scase_index)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(REALSXP, LENGTH(Scase_index)));
  for(i = 0; i < LENGTH(Scase_index); i++) {
    if(h_node_case_is_set(node, (size_t) INTEGER(Scase_index)[i]))
      REAL(ret)[i] = (double) h_node_get_case_value(node, (size_t) INTEGER(Scase_index)[i]);
    else
      REAL(ret)[i] = NA_REAL;
  }

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_unset_case(SEXP Snode, SEXP Scase_index)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status = (h_status_t) 0;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = 0;

  for(i = 0; i < LENGTH(Scase_index); i++) {
    status = h_node_unset_case(node, (size_t) INTEGER(Scase_index)[0]);

    if(status != 0) {
      INTEGER(ret)[0] = (int) status;
      UNPROTECT(1);
      return ret;
    }
  }

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_case_is_set(SEXP Snode, SEXP Scase_index)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0;

  node = nodePointerFromSEXP(Snode);

  PROTECT(ret = allocVector(LGLSXP, LENGTH(Scase_index)));
  for(i = 0; i < LENGTH(Scase_index); i++)
    LOGICAL(ret)[i] = (int) h_node_case_is_set(node, (size_t) INTEGER(Scase_index)[i]);

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_domain_set_case_count(SEXP Sdomain, SEXP Scase_index, SEXP Scase_count)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_status_t status = (h_status_t) 0;
  int i = 0;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = 0;

  for(i = 0; i < LENGTH(Scase_index); i++) {
    status = h_domain_set_case_count(domain, (size_t) INTEGER(Scase_index)[i],
                                     (h_number_t) REAL(Scase_count)[i]);
    if(status != 0) {
      INTEGER(ret)[0] = (int) status;
      UNPROTECT(1);
      return ret;
    }
  }

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_domain_get_case_count(SEXP Sdomain, SEXP Scase_index)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  int i = 0;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, LENGTH(Scase_index)));

  for(i = 0; i < LENGTH(Scase_index); i++)
    REAL(ret)[i] = (double) h_domain_get_case_count(domain, (size_t) INTEGER(Scase_index)[i]);

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_domain_enter_case(SEXP Sdomain, SEXP Scase_index)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_enter_case(domain, (size_t) INTEGER(Scase_index)[0]);
  UNPROTECT(1);

  return ret;
}


/* Section 11.2 Scoring of graphical models */

SEXP RHugin_domain_get_log_likelihood(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_log_likelihood(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_AIC(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_AIC(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_BIC(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_BIC(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 11.3 Data files */

// SEXP RHugin_domain_parse_cases(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_handler, SEXP Sdata)
// SEXP RHugin_domain_save_cases(SEXP Sdomain, SEXP Sfile_name, SEXP Snodes, SEXP Scases,
//                               SEXP Sinclude_case_counts, SEXP Sseparator, SEXP Smissing_data)


/* Section 11.4 Learning network structure */

SEXP RHugin_domain_learn_structure(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_learn_structure(domain);
  UNPROTECT(1);

  return ret;
}
  

SEXP RHugin_domain_set_significance_level(SEXP Sdomain, SEXP Sprobability)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_set_significance_level(domain, (h_double_t) REAL(Sprobability)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_significance_level(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_significance_level(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 11.5 Domain knowledge */

SEXP RHugin_node_set_edge_constraint(SEXP Sa, SEXP Sb, SEXP Sconstraint)
{
  SEXP ret = R_NilValue;
  h_node_t a = NULL, b = NULL;
  h_edge_constraint_t constraint = h_constraint_error;

  a = nodePointerFromSEXP(Sa);
  b = nodePointerFromSEXP(Sb);

  if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_NONE)
    constraint = h_constraint_none;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_EDGE_REQUIRED)
    constraint = h_constraint_edge_required;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_EDGE_FORBIDDEN)
    constraint = h_constraint_edge_forbidden;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_FORWARD_EDGE_REQUIRED)
    constraint = h_constraint_forward_edge_required;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_BACKWARD_EDGE_REQUIRED)
    constraint = h_constraint_backward_edge_required;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_FORWARD_EDGE_FORBIDDEN)
    constraint = h_constraint_forward_edge_forbidden;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_BACKWARD_EDGE_FORBIDDEN)
    constraint = h_constraint_backward_edge_forbidden;

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_set_edge_constraint(a, b, constraint);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_edge_constraint(SEXP Sa, SEXP Sb)
{
  SEXP ret = R_NilValue;
  h_node_t a = NULL, b = NULL;
  h_edge_constraint_t constraint = h_constraint_error;

  a = nodePointerFromSEXP(Sa);
  b = nodePointerFromSEXP(Sb);
  constraint = h_node_get_edge_constraint(a, b);

  PROTECT(ret = allocVector(STRSXP, 1));

  switch(constraint) {
    case h_constraint_none:
      SET_STRING_ELT(ret, 0, mkChar("none"));
      break;

    case h_constraint_edge_required:
      SET_STRING_ELT(ret, 0, mkChar("edge.required"));
      break;

    case h_constraint_edge_forbidden:
      SET_STRING_ELT(ret, 0, mkChar("edge.forbidden"));
      break;

    case h_constraint_forward_edge_required:
      SET_STRING_ELT(ret, 0, mkChar("forward.edge.required"));
      break;

    case h_constraint_backward_edge_required:
      SET_STRING_ELT(ret, 0, mkChar("backward.edge.required"));
      break;

    case h_constraint_forward_edge_forbidden:
      SET_STRING_ELT(ret, 0, mkChar("forward.edge.forbidden"));
      break;

    case h_constraint_backward_edge_forbidden:
      SET_STRING_ELT(ret, 0, mkChar("backward.edge.forbidden"));
      break;

    case h_constraint_error:
      SET_STRING_ELT(ret, 0, mkChar("error"));
      break;
  }

  UNPROTECT(1);
  return ret;
}


/* Section 11.6 Learning conditional probability tables */

SEXP RHugin_domain_learn_tables(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_learn_tables(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_set_log_likelihood_tolerance(SEXP Sdomain, SEXP Stolerance)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_set_log_likelihood_tolerance(domain, (h_double_t) REAL(Stolerance)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_log_likelihood_tolerance(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_log_likelihood_tolerance(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_set_max_number_of_em_iterations(SEXP Sdomain, SEXP Scount)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_set_max_number_of_em_iterations(domain, (size_t) INTEGER(Scount)[0]);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_get_max_number_of_em_iterations(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_max_number_of_em_iterations(domain);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_domain_learn_class_tables(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_learn_class_tables(domain);
  UNPROTECT(1);

  return ret;
}


/* Section 12.8 parsing NET files */

SEXP RHugin_net_parse_domain(SEXP Sfile_name)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = h_net_parse_domain((h_string_t) CHAR(asChar(Sfile_name)),
                                         RHuginParseNETError,
                                         NULL);

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_delete); 
  }

  return ret;
}


SEXP RHugin_domain_save_as_net(SEXP Sdomain, SEXP Sfile_name)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_save_as_net(domain, (h_string_t) CHAR(asChar(Sfile_name)));
  UNPROTECT(1);

  return ret;
}


/* Section 13.2 the position of a node */

SEXP RHugin_node_set_position(SEXP Snode, SEXP Sposition)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status;

  node = nodePointerFromSEXP(Snode);
  status = h_node_set_position(node, (h_coordinate_t) INTEGER(Sposition)[0],
                              (h_coordinate_t) INTEGER(Sposition)[1]);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) status;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_node_get_position(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_status_t status;
  h_coordinate_t position[] = {0, 0};

  node = nodePointerFromSEXP(Snode);
  status = h_node_get_position(node, position, position + 1);

  if(status == h_error_none) {
    PROTECT(ret = allocVector(INTSXP, 2));
    INTEGER(ret)[0] = (int) position[0];
    INTEGER(ret)[1] = (int) position[1];
    UNPROTECT(1);
  }

  return ret;
}


/* Section 13.3 the size of a node */


