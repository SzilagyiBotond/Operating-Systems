BEGIN{
}
$NR % 2 == 0
{
print NR,$0
}
END{
}
