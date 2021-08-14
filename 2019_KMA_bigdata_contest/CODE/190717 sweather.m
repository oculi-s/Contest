clear all

pngFiles = dir('*.png');
numfiles = length(pngFiles);
mydata = cell(1, numfiles);

for k = 1:numfiles
    mydata{k} = imread(pngFiles(k).name);
    tempdata = cell2mat(mydata(k));
    tempname = string(pngFiles(k).name);
    tempsize = size(tempdata);    
    
    IMGR = tempdata(:,:,1);
    IMGG = tempdata(:,:,2);
    IMGB = tempdata(:,:,3);
    
    IMGR = IMGR == 157;
    IMGG = IMGG == 186;
    IMGB = IMGB == 209;
    
    FMAP = [IMGR IMGG IMGB];
    FMAP = reshape(FMAP, tempsize);
    FMAP = min(FMAP, [], 3);
    
    NAME(k) = sscanf(tempname, "%d");
    VAL(k) = round(nnz(FMAP)/numel(FMAP)*100,1);
    DATA(k,:) = [NAME(k) VAL(k)];
    
%      clear tempdata tempname tempsize VAL NAME IMGR IMGG IMGB FMAP
end

%  clear pngFiles numfiles mydata k
table(DATA)