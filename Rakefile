task :default => ['vfh.o']

file 'vfh.o' => ['vfh.c', 'vfh.h'] do
  sh "gcc vfh.c -c -o vfh.o -Wall"
end