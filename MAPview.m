function MAP = MAPview(MAT, PATH)
    
    if(isdir("MAP_VIEW"))
        rmdir MAP_VIEW s;
    end
    mkdir MAP_VIEW;

    cd(PATH.file);
    SHPemd = shaperead('TL_SCCO_EMD.shp');
    SHPsig = shaperead('TL_SCCO_SIG.shp');
    AREA = [11010 11110 11130 31021 31022 31023];
    AREAshp = [11110 11350 11410 41131 41133 41135];
    AREAname = ["서울종로구" "서울노원구" "서울서대문구" "성남수정구" "성남중원구" "성남분당구"];
    
    sumdata2 = 0;
    sumdata3 = 0;
    for i = 1:length(MAT.TIME)/2
        temp2 = cell2mat(MAT.TIME(i));
        temp3 = cell2mat(MAT.TIME(i+12));
        temp2index = unique(MAT.TIME{i}(:,2));
        temp3index = unique(MAT.TIME{i+12}(:,2));
            for j = 1:length(temp2index)
                position2 = find(~(temp2(:,2)-temp2index(j)));
                tempdata2(j,5:28) = mean(temp2(position2,5:end),1)*5;
                
                position3 = find(~(temp3(:,2)-temp3index(j)));
                tempdata3(j,5:28) = mean(temp3(position3,5:end),1)*5;
                
                indexdata2(j,1:4) = temp2(position2(1),1:4);
                indexdata3(j,1:4) = temp3(position3(1),1:4);
            end
            sumdata2 = sumdata2+tempdata2;
            sumdata3 = sumdata3+tempdata3;
    end
    sumdata2(:,1:4) = indexdata2;
    sumdata3(:,1:4) = indexdata3;
    
    temp = str2num(cell2mat({SHPemd.EMD_CD}'));
    temp1 = str2num(cell2mat({SHPsig.SIG_CD}'));
    temparea = floor(temp/1e+3);
    temparea2 = floor(sumdata2(:,2)/1e+15);
    
    for i = 1:length(AREA)
        fig = figure;
        position = find(~(temparea-AREAshp(i)));
        for k = 1:length(position)
            coor = rmmissing([SHPemd(position(k)).X; SHPemd(position(k)).Y],2);
            hold on; plot(coor(1,:), coor(2,:), 'color', '#a3a3a3');
        end
        
        position = find(~(temp1-AREAshp(i)));
        bound = SHPsig(position).BoundingBox;
        
        position = find(~(temparea2-AREA(i)));
        coor = sumdata2(position,3:4);
        margin = 0.001;
        xlimit = [bound(1,1)*(1-margin) bound(2,1)*(1+margin)];
        ylimit = [bound(1,2)*(1-margin) bound(2,2)*(1+margin)];
        set(gca,'xlim',xlimit,'ylim',ylimit);
        
        for k = 28-8:28
            hold on;
            set(gcf,'Visible', 'off', 'position', [0 0 500 1000]);
            
            rad1 = sumdata2(position,k)/100*8;
            tempfig1 = viscircles(round(coor), rad1, 'color', 'red');
            tempname = AREAname(i)+' 2017년 '+string(k-5)+'시 유동인구 지도';
            title(tempname);

            cd(PATH.map);
            saveas(fig, tempname+'.png');
            delete(tempfig1);
        end
        
        for k = 28-8:28
            hold on;
            set(gcf,'Visible', 'off', 'position', [0 0 500 1000]);
            
            subplot(1,9,k-23);
            rad2 = sumdata3(position,k)/100*8;
            tempfig2 = viscircles(round(coor), rad2, 'color', 'blue');
            tempname = AREAname(i)+' 2018년 '+string(k-5)+'시 유동인구 지도';
            title(tempname);

            cd(PATH.map);
            saveas(fig, tempname+'.png');
%             delete(tempfig2);
        end
    end
end