sysfs_tgt:
	gcc -Wall test_sysfs.c -o test_sysfs -lsysapi -pthread

syswq_tgt:
	gcc -Wall test_syswq.c -o test_syswq -lsysapi -pthread

sysnet_tgt:
	gcc -Wall test_sysnet.c -o test_sysnet -lsysapi -pthread

sysevent_tgt:
	gcc -Wall test_sysevent.c -o test_sysevent -lsysapi -pthread

sysgc_tgt:
	gcc -Wall test_sysgc.c -o test_sysgc -lsysapi -pthread

syscsv_tgt:
	gcc -Wall test_syscsv.c -o test_syscsv -lsysapi -pthread

syscirque_tgt:
	gcc -Wall test_syscirque.c -o test_syscirque -lsysapi -pthread

syslist_tgt:
	gcc -Wall test_syslist.c -o test_syslist -lsysapi -pthread

sysqueue_tgt:
	gcc -Wall test_sysqueue.c -o test_sysqueue -lsysapi -pthread

sysutil_tgt:
	gcc -Wall test_sysutil.c test_getline.c test_getdelim.c -o test_sysutil -lsysapi -pthread

all: sysutil_tgt syslist_tgt syscirque_tgt syscsv_tgt sysgc_tgt sysevent_tgt sysnet_tgt syswq_tgt sysfs_tgt sysqueue_tgt

clean:
	rm -rf test_sysutil test_syslist test_syscirque test_syscsv test_sysgc test_sysevent test_sysnet tset_syswq test_sysfs test_sysqueue
