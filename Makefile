tistory-upload:
    git add .
    git commit -m "upload"
    git push origin main
    sleep 60  # 60�� ��� ��ɾ�
    git pull origin main #  �ٽ� pull�� �޴� ������ ���� ����� actions�� ������ �����ϱ� �����̴�.