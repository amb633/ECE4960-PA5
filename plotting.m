clc , clear , close all;

filenames = {'FORWARD_EULER_Results.txt' ; 'HEUN_ONE_Results.txt' ; ...
    'HEUN_ITR_Results.txt' ; 'RK34_Results.txt' ; 'RK34A_Results.txt'};

for f = 1:length(filenames) %specifiy index if you only want to plot one
filename = string(filenames{f});

% open desired file
fileID = fopen(filename);

% find the number of data entries by counting the number of lines
N = -1;  % counting from -1 to account for header line
while ~feof(fileID)
    tline = fgetl(fileID);
    N = N + 1;
end
frewind(fileID);

% read the header 
headers = string(fgetl(fileID));
headers = strsplit( headers );

% find the number of bodies from the headers
n_bodies = floor( length(headers) / 3 );
n_data = n_bodies*3+1;

% parse the headers to get individual body names
body_names = [];
for i = 1:n_bodies 
    body_name = strsplit( headers(i*3) , '_' );
    body_name = body_name(1);
    body_names = [body_names ; body_name];
end

% variables to store the parsed data
time_log = zeros( N , 1 );

position_log = zeros( N , 3 , n_bodies );
% read each data line and store it
for i = 1:N
    data = textscan(fileID , '%f' , n_data );
    data = cell2mat( data );
    time_log = data(1);
    data = data(2:end);
    data = reshape( data , [3 , n_bodies] );
    position_log( i , : , : ) = data;
end
fclose(fileID);

% plot the parsed data
% assuming that the first body is some central body
figure(); hold on; grid on;
plot3( position_log(:,1,1) , position_log(:,2,1) , position_log(:,3,1) , ...
        'ro' , 'MarkerSize' , 14 , 'MarkerFaceColor' , 'r');
    
for id = 2:n_bodies
    plot3( position_log(:,1,id) , position_log(:,2,id) , position_log(:,3,id) , 'LineWidth' , 2 );
end

legend(body_names);
end