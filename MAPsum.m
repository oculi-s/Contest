function MAPS = MAPsum(NEW, PATH)

    if(isdir("MAP_NEW"))
        rmdir MAP_NEW s;
    end
    mkdir MAP_NEW;

    cd(PATH.file);
    SHPemd = shaperead('TL_SCCO_EMD.shp');
    SHPsig = shaperead('TL_SCCO_SIG.shp');
    AREA = [11010 11110 11130 31021 31022 31023];
    AREAshp = [11110 11350 11410 41131 41133 41135];
    AREAname = ["�������α�" "��������" "���Ｍ�빮��" "����������" "�����߿���" "�����д籸"];   
    
    for i = 1:length(NEW.TIME)/2
        temp = str2num(cell2mat({SHPemd.EMD_CD}'));
        temparea = floor(temp/1e+3);
        
        fig = figure;
        for j = 1:length(AREA)
            position = find(~(temparea-AREAshp(j)));
            for k = 1:length(position)
                coor = rmmissing([SHPemd(position(k)).X; SHPemd(position(k)).Y],2);
                hold on; plot(coor(1,:), coor(2,:), 'color', '#a3a3a3');
            end
        end
        
        temp1 = str2num(cell2mat({SHPsig.SIG_CD}'));
        temp2 = cell2mat(NEW.TIME(i));
        temp3 = cell2mat(NEW.TIME(i+12));
        temparea = rmmissing(floor(temp2(:,2)/1e+15));
        
        image = cell(1);
        coor = [];
        for k = 28-8:28
            for j = 1:length(AREA)
                position = find(~(temp1-AREAshp(j)));
                tempsize = SHPsig(position).BoundingBox;

                position1 = find(~(temparea-AREA(j)))+1;
                coor(j,:) = mean(rmmissing([SHPsig(position).X; SHPsig(position).Y],2),2);
            end
            
            rad1 = power(2.2,(temp2(2:end,k)/5e4))*500;
            rad2 = power(2.2,(temp3(2:end,k)/5e4))*500;
            hold on; 
            
            set(gcf,'Visible', 'off', 'position', [0 0 600 1000]);
            set(gca,'xlim', [9.4 9.8]*1e5, 'ylim', [1.92 1.97]*1e6);
            tempfig1 = viscircles(round(coor), rad1, 'color', 'red');
            tempfig2 = viscircles(round(coor), rad2, 'color','blue');
                
            cd(PATH.maps);
            tempname = string(NEW.TIME{i}(2,1))+' vs '+string(NEW.TIME{i}(3,1))+' '+string(k-5)+'�� �����α� ����';
            title(tempname);
            legend([tempfig1 tempfig2], {string(NEW.TIME{i}(2,1)), string(NEW.TIME{i+12}(2,1))});
            saveas(fig, tempname+'.png');
            image{end+1} = imread(tempname+'.png');
            
            delete(tempfig1);
            delete(tempfig2);
        end
        
        tempname = string(NEW.TIME{i}(2,1))+' �����α� ����';
        vid = VideoWriter(tempname+'.avi','Uncompressed AVI');
        vid.FrameRate = 4;
        open(vid);
        for l = 2:length(image)
            tempvid(:,:,:,l-1) = (image{l}(:,:,:));
        end
        writeVideo(vid,tempvid);
        close(vid);
    end
    
    temp1 = str2num(cell2mat({SHPsig.SIG_CD}'));
    temp2 = [];
    temp3 = [];
    for n = 1:length(NEW.TIME)/2
        temp2 = temp2+cell2mat(NEW.TIME(n));
        temp3 = temp3+cell2mat(NEW.TIME(n+12));
    end
    temparea = rmmissing(floor(temp2(:,2)/1e+15));

    image = cell(1);
    coor = [];
    for k = 28-8:28
        for j = 1:length(AREA)
            position = find(~(temp1-AREAshp(j)));
            tempsize = SHPsig(position).BoundingBox;

            position1 = find(~(temparea-AREA(j)))+1;
            coor(j,:) = mean(rmmissing([SHPsig(position).X; SHPsig(position).Y],2),2);
        end

        rad1 = power(2.2,(temp2(2:end,k)/5e4))*500;
        rad2 = power(2.2,(temp3(2:end,k)/5e4))*500;
        hold on; 

        set(gcf,'Visible', 'off', 'position', [0 0 600 1000]);
        set(gca,'xlim', [9.4 9.8]*1e5, 'ylim', [1.92 1.97]*1e6);
        tempfig1 = viscircles(round(coor), rad1, 'color', 'red');
        tempfig2 = viscircles(round(coor), rad2, 'color','blue');

        cd(PATH.maps);
        tempname = '2017 vs 2018 '+string(k-5)+'�� �����α� ����';
        title(tempname);
        legend([tempfig1 tempfig2], {string(NEW.TIME{i}(2,1)), string(NEW.TIME{i+12}(2,1))});
        saveas(fig, tempname+'.png');
        image{end+1} = imread(tempname+'.png');

        delete(tempfig1);
        delete(tempfig2);
    end

    tempname = string(NEW.TIME{i}(2,1))+' �����α� ����';
    vid = VideoWriter(tempname+'.avi','Uncompressed AVI');
    vid.FrameRate = 4;
    open(vid);
    for l = 2:length(image)
        tempvid(:,:,:,l-1) = (image{l}(:,:,:));
    end
    writeVideo(vid,tempvid);
    close(vid);
end