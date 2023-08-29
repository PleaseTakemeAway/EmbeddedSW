tistory-upload:
    git add .
    git commit -m "upload"
    git push origin main
    sleep 60  # 60초 대기 명령어
    git pull origin main #  다시 pull을 받는 이유는 원격 저장소 actions가 파일을 변경하기 때문이다.