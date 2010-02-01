get.entropy <- function(domain, node, other = NULL)
{
  RHugin.check.args(domain, c(node, other), character(0), "get.entropy")

  if(is.null(other)) {
    node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain, node,
                        PACKAGE = "RHugin")
    ans <- .Call("RHugin_node_get_entropy", node.ptrs, PACKAGE = "RHugin")
    names(ans) <- node
  }

  else {
    if(length(node) != length(other))
      stop(sQuote("node"), " and ", sQuote("other"), " are not the same length")

    node.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                        as.character(node), PACKAGE = "RHugin")
    other.ptrs <- .Call("RHugin_domain_get_node_by_name", domain,
                         as.character(other), PACKAGE = "RHugin")
    ans <- .Call("RHugin_node_get_mutual_information", node.ptrs, other.ptrs,
                  PACKAGE = "RHugin")

    names(ans) <- paste(node, other, sep = "~")
  }

  ans
}

