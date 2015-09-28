library(ggplot2)
filename <- "v100r100.degrees"
args <- commandArgs(TRUE)
stopifnot(length(args) >= 2)
input <- args[1:(length(args)-1)]
output <- tail(args, n = 1)

# Colorblind friendly palette
cbbPalette <- c("#000000", "#E69F00", "#56B4E9", "#009E73", "#F0E442", "#0072B2", "#D55E00", "#CC79A7")

png(file = output, width = 1200, height = 1000)
  plot <- ggplot()
  data <- data.frame()
  for( i in 1:length(input) ){
    degrees <- read.csv(input[i], header = TRUE)
    mod_degree <- data.frame(degrees[1], 1 - cumsum(degrees[2]) / sum(degrees[2]), group=input[i])
    data <- rbind(data, mod_degree)
  }
  ggplot() + geom_point(data=data, aes(x=value, y=count, color=group)) + scale_x_log10() + scale_y_log10() + theme(legend.position = "bottom")
dev.off()
