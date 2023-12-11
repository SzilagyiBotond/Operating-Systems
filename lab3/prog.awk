BEGIN{
	sum1=0
	sum2=0
}
$5 ~ / [A]$ /
{
sum+=1
}
END{
print sum
}
