clear all

cd '\Users\kjunhun9\Documents\MATLAB\input_data'
pngFiles = dir('*.png');
numfiles = length(pngFiles);
mydata = cell(1, numfiles);

data = xlsread("data_predicted.xlsx","data");
data(:,5) = data(:,3);

time = datetime(data(:,2)-1, 'ConvertFrom', 'datenum');
data(:,2) = year(time)-100;
data(:,3) = month(time);
data(:,4) = day(time);

for i = 1:numfiles
    cd '\Users\kjunhun9\Documents\MATLAB\input_data'
    mydata{i} = imread(pngFiles(i).name);
    tempdata = cell2mat(mydata(i));
    tempname = string(pngFiles(i).name);
    NAME(i) = sscanf(tempname, "%d");
    
    tempdata = rgb2hsv(tempdata);
    IMGH = tempdata(:,:,1);
    IMGS = tempdata(:,:,2);
    IMGV = tempdata(:,:,3);
    
    tempindex = find(data(:,1) == NAME(i));
    weightdata = data(tempindex, 5);
    
    for j = 1:length(tempindex)
        if NAME(i) == 185
%         if weightdata(j) > 0.5
            filename = strings(1,4);
            filename(1) = NAME(i);
            filename(2:4) = data(tempindex(j),2:4);
            filename = join(filename);
            filename = join([filename,".png"]);
            
            epsilon = 0.001;
            NEWV = immultiply(IMGV, abs(IMGV-0.82)<epsilon) * weightdata(j);
            image(:,:,1) = IMGH;
            image(:,:,2) = IMGS;
            image(:,:,3) = IMGV - NEWV;
            image = hsv2rgb(image);
            
            cd '\Users\kjunhun9\Documents\MATLAB\output_data'
            imwrite(image, filename);
        end
    end
end