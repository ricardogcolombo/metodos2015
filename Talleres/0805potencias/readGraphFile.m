function s = readGraphFile(filename)

s = struct('n',0,'m',0,'out',[],'origin',[],'dest',[],'vals',[]);
file_id = fopen(filename);

line = fgets(file_id);
s.n = sscanf(line, '%d');
line = fgets(file_id);
s.m = sscanf(line, '%d');

s.out = zeros(s.n,1);
s.origin = zeros(s.m,1);
s.dest = zeros(s.m,1);
s.vals = zeros(s.m,1);

index = 1;

while ~feof(file_id)
    line = fgets(file_id);
    nums = sscanf(line,'%d %d');
    s.origin(index) = nums(1);
    s.dest(index) = nums(2);
    s.out(nums(1)) = s.out(nums(1)) + 1;
    index = index + 1;
end

end