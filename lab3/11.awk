BEGIN{
 s=0
nr=0
}
{
	nr++
	s+=$2
}
END{
print s/nr
}
