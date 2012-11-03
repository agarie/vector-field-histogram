task :default => [:compile, :example, :cleanup]

task :compile => ['vfh.o']

task :example => ['no-velocity'] do
  sh "./no-velocity"
end

task :cleanup do
  sh "rm no-velocity vfh.o"
end

file 'vfh.o' => ['vfh.c', 'vfh.h'] do
  sh "gcc vfh.c -c -o vfh.o -Wall"
end

file 'no-velocity' => ['examples/no-velocity.c', 'vfh.o', 'vfh.h'] do
  sh "gcc examples/no-velocity.c vfh.o -Wall -I. -o no-velocity"
end