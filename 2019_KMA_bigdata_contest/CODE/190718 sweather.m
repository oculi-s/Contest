clear all

% 1. data read
data = xlsread("data.xlsx");
data = data .* ~isnan(data);
data_size = size(data);

tempdata = data(1:data_size(1), 2:data_size(2));
data_normalized = normalize(tempdata, 'range');

x_data = data_normalized(1:data_size(1), 1:data_size(2)-1);
y_data = data_normalized(1:data_size(1), data_size(2)-1);

layers = [data_size(2)-1 32 16 128 data_size(1)];
n = length(layers);

L = x_data;
for i = 1:n-1
    W{i} = rand([layers(i) layers(i+1)]);
    L = L * W{i};
end

clear tempdata
clear i

