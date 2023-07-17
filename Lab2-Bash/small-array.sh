for((i=0;i<2;i++))
 do
 echo " enter $((i+1)) number"
 read nos[$i]
 done
 echo "Number entered are"
 for((i=0;i<2;i++))
 do
 echo ${nos[$i]}
 done
 small=${nos[0]}
 for((i=0;i<2;i++))
 do
 if [ ${nos[$i]}-lt $small ];then
 small=${nos[$i]}
 fi
 done
 echo "Smallest Number in the array is :" $small