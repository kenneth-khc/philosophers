if [ $1 ]
then
	philo_count=$1
else
	philo_count=7
fi

output_file=$(dirname $0)/output.log
if [ ! -e $output_file ]; then
	touch $output_file
fi

start=1
for i in $(seq $start $philo_count)
do
eat_count=$(cat $output_file | grep "$i is eating" | wc -l | tr -d ' ')
echo "Philo $i ate $eat_count times"
done