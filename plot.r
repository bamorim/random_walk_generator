library(ggplot2)
filename <- "v100r100.degrees"
csv <- paste0("/home/bamorim/ufrj/land/", filename, ".csv")
# it should receive as parameters the files to plot and an output png file

degrees <- read.csv(csv, header = TRUE)
mod_degree <- data.frame(degrees[1], 1 - cumsum(degrees[2]) / sum(degrees[2]))
png(file = "foo.png", width = 800, height = 600)
ggplot() + geom_point(data=mod_degree, aes(x=degree, y=count)) + scale_x_log10() + scale_y_log10()
dev.off()
