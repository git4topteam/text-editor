@echo off
setlocal
docker build -t img4topteam.1 .
docker tag img4topteam.1:latest topteam.ci.environment:img4topteam.1
docker tag topteam.ci.environment:img4topteam.1 docker4topteam/topteam.ci.environment:img4topteam.1
docker push docker4topteam/topteam.ci.environment:img4topteam.1
endlocal
