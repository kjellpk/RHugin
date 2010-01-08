plot.RHuginDomain <- function(x, y, ...)
{
  if(!require(Rgraphviz))
    stop("plotting an RHugin domain requires the Rgraphviz ",
         "package - please install Rgraphviz and try again")

  nodes <- get.nodes(x)
  node.summary <- summary(x, nodes = nodes)$nodes
  fill <- character(length(nodes))
  shape <- character(length(nodes))
  names(fill) <- names(shape) <- nodes

  for(node in nodes) {
    if(node.summary[[node]]$category == "decision") {
      fill[node] <- "red"
      shape[node] <- "rectangle"
    }
    else if(node.summary[[node]]$category == "utility") {
      fill[node] <- "green"
      ## diamond not yet supported by Rgraphviz ##
      #shape[node] <- "diamond"
      shape[node] <- "rectangle"
    }
    else {
      if(!is.null(node.summary[[node]]$kind) &&
          node.summary[[node]]$kind == "discrete")
      {
        fill[node] <- "yellow"
        shape[node] <- "ellipse"
      }
      else {
        fill[node] <- "orange"
        shape[node] <- "ellipse"
      }
    }
  }

  gx <- as.graph.RHuginDomain(x)
  nodeRenderInfo(gx) <- list(fill = fill, shape = shape, lwd = 3)
  edgeRenderInfo(gx) <- list(lwd = 2)
  gx <- layoutGraph(gx, layoutFun = layoutRHugin, domain = x)
  renderGraph(gx)

  invisible(gx)
}


