% function MAPcon(PATH)
    cd(PATH.map)
    ALL = dir('*png');
    
%     for i = 1:12
        figure;
        image = [];
        for j = 1:9
            temp = imread(ALL(j).name);
            image(:,:,:,j) = temp(:,:,:);
        end
        temp = reshape(image, [size(image,1) size(image,2)*9 3]);
        imshow(temp);
    
    
% end