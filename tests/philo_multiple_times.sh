if [ $# -lt 4 ] || [ $# -gt 5 ]; then
	echo "Invalid args"
	exit 1
fi

# Runs philosophers for $timeout seconds and checks if a philo died or not
# Usage: same as running ./philo but replace with ./philo_multi
# eg. ./philo_multi 4 410 200 200

philo="./philo"
cp $philo ../tests/test_philo
command="./test_philo $@"
timeout=30 # How long the simulation should run for before getting terminated
log_dir="../tests/logs/"
file_name="test"
extension=".log"
results=""$log_dir"results.txt"

if [ -e $log_dir ]; then
	rm -rf $log_dir
fi

mkdir -p $log_dir

for i in {1..100}
do
log_file="${log_dir}${file_name}${i}${extension}"
( eval $command > $log_file ) & pid=$!
( sleep $timeout && kill $pid && pkill test_philo ) 2>/dev/null & watcher=$! # kills all processes named test_philo
wait $pid 2>/dev/null && pkill -HUP -P $watcher
sleep 1
died=$(cat $log_file | grep "died" | wc -l | tr -d ' ')

	if [[ $died -eq 0 ]]; then
		echo "Test $i NO PHILO DIED" >> $results
	else
		echo "Test $i A PHILO DIED" >> $results
	fi

done

rm -rf test_philo

echo "\033[0;32mDone!\033[0m"
