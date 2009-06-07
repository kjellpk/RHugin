plot.RHuginDomain <- function(x, y, ...)
{
  if(!is.element("package:Rgraphviz", search()))
    stop("plotting an RHugin domain requires the Rgraphviz ",
         "package - please load Rgraphviz and try again")

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
      shape[node] <- "rectangle"
    }
    else {
      fill[node] <- "yellow"
      shape[node] <- "ellipse"
    }
  }

  gx <- as.graph.RHuginDomain(x)
  nodeRenderInfo(gx) <- list(fill = fill, shape = shape, lwd = 3)
  edgeRenderInfo(gx) <- list(lwd = 2)
  gx <- layoutGraph(gx, layoutFun = layoutRHugin, domain = x)
  renderGraph(gx)

  invisible(gx)
}


