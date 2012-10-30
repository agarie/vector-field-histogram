task :default => [:compile, :example]

task :compile => ['vfh.o']

task :example => ['no-velocity'] do
  sh "./no-velocity"
end

file 'vfh.o' => ['vfh.c', 'vfh.h'] do
  sh "gcc vfh.c -c -o vfh.o -Wall"
end

file 'no-velocity' => ['examples/no-velocity.c', 'vfh.o', 'vfh.h'] do
  sh "gcc examples/no-velocity.c vfh.o -I. -o no-velocity"
end