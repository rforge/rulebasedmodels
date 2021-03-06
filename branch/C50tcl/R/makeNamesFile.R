## TODO:
##     fix call printing


makeNamesFile <-
function(x, y, w = NULL, label = "outcome", comments = TRUE)
  {
    if(comments)
      {
        call <- match.call()
        out <- paste("| Generated using ", R.version.string, "\n",
                     "| on ", format(Sys.time(), "%a %b %d %H:%M:%S %Y"), "\n",
                     "| function call: ", paste(deparse(call)),
                     sep = "")
      } else out <- ""

    if(is.numeric(y))
      {
        outcomeInfo <- ": continuous."
      } else {
        lvls <- levels(y)
        prefix <- if(is.ordered(y)) "[ordered] " else ""
        outcomeInfo <- paste(": ",
                             prefix,
                             paste(lvls, collapse = ","),
                             ".", sep = "")
      }

    out <- paste(out,
                 "\n", label, ".\n",
                 "\n", label, outcomeInfo,
                 sep = "")
    varData <- QuinlanAttributes(x)
    varData <- paste(names(varData), ": ", varData, sep = "", collapse = "\n")
    out <- paste(out, "\n", varData, "\n", sep = "")
    out


  }


makeCostFile <- function(cst)
  {
    classes <- colnames(cst)  
    out <- ""
    for(i in 1:nrow(cst))
      {
        for(j in 1:ncol(cst))
          {
            if(i != j)
              {
                if(cst[i,j] > 0)
                  {
                    out <- paste(out,
                                 paste(classes[i], ", ", classes[i],
                                       ": ", cst[i,j], sep = ""),
                                 sep = "\n")
                  }
              }
          }
      }
      out
  }
