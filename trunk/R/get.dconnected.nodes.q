get.dconnected.nodes <- function(domain, source, hard, soft)
{
  if(missing(hard)) hard <- character(0)
  if(missing(soft)) soft <- character(0)

  RHugin.check.args(domain, c(source, hard, soft), character(0),
                    "get.dconnected.nodes")

  source.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, source,
                        PACKAGE = "RHugin")
  hard.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, hard,
                      PACKAGE = "RHugin")
  soft.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, soft,
                      PACKAGE = "RHugin")

  dc.ptrs <- .Call("RHugin_domain_get_d_connected_nodes", domain, source.ptrs,
                    hard.ptrs, soft.ptrs, PACKAGE = "RHugin")

  names(dc.ptrs)
}

