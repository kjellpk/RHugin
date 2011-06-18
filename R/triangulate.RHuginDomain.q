triangulate.RHuginDomain <- function(object, method = "best.greedy", order,
                                     max.separators = 100000, ...)
{
  RHugin.check.domain(object, "triangulate")
  methods <- c("clique.size", "clique.weight", "fill.in.size", "fill.in.weight",
               "best.greedy", "total.weight")
  method <- match.arg(method, choices = methods)

  if(.Call("RHugin_domain_is_triangulated", object, PACKAGE = "RHugin"))
    stop(deparse(substitute(object)), " is aleady triangulated")

  if(!missing(order)) {
    node.ptrs <- .Call("RHugin_domain_get_node_by_name", object, order,
                        PACKAGE = "RHugin")
    .Call("RHugin_domain_triangulate_with_order", object, node.ptrs,
           PACKAGE = "RHugin")
  }

  else {
    if(method == "total.weight")
      .Call("RHugin_domain_set_max_number_of_separators", object,
             max.separators, PACKAGE = "RHugin")

    .Call("RHugin_domain_triangulate", object, method, PACKAGE = "RHugin")
  }

  order <- .Call("RHugin_domain_get_elimination_order", object,
                  PACKAGE = "RHugin")
  names(order)
}


