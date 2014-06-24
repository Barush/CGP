args <- commandArgs(trailingOnly = TRUE)
filename <- args[1]
x_lab <- args[3]
y_lab <- args[4]

a <- read.table(args[2])
a <- t(a)
pdf(filename)

#boxplot(a[,1], a[,2], a[,3], a[,4], a[,5] xlab = x_lab, ylab = y_lab, 
#	names=c("F1", "F2", "F3", "F4", "F5"))

boxplot(a[,1], a[,2],  xlab = x_lab, ylab = y_lab, 
	names=c("test 8", "test 16"))
dev.off()