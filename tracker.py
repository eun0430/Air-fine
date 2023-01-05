import cv2
import sys

if __name__ == '__main__' :

    tracker = cv2.TrackerCSRT_create()

    # 카메라를 연결해 실시간으로 받아오는 영상을 저장 video에 저장
    video = cv2.VideoCapture(0)

    # 연결되지 않았을때에 대한 조건
    if not video.isOpened():
        print("Could not open video")
        sys.exit()

    # 측정할 객체를 선택하기 위해 영상의 첫번째 화면 읽어오기
    ok, frame = video.read()
    if not ok:
        print('Cannot read video file')
        sys.exit()
    
    # 객체 선택 초기 박스 지정 (객체 선택 전 초기값, 아무 의미 없는 숫자임)
    bbox = (287, 23, 86, 320)

    bbox = cv2.selectROI(frame, False)

    # 위에 지정해준 박스 값으로 초기화
    ok = tracker.init(frame, bbox)

    while True:
        # 프레임 읽어오기
        ok, frame = video.read()
        if not ok:
            break
        
        # 타이머 시작
        timer = cv2.getTickCount()

        # tracker 값 계속 업데이트
        ok, bbox = tracker.update(frame)
        print(bbox)

        # 초당 프레임 수 계산 (FPS) # 여기 파트는 속도 조절과 상관 없음
        fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer);

        # 관심영역(측정할 객체) 선택
        if ok:
            # 객체를 측정했을 시 따라 추적하는 내용
            p1 = (int(bbox[0]), int(bbox[1]))
            p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
            cv2.rectangle(frame, p1, p2, (255,0,0), 2, 1)
        else :
            # 객체를 측정 못할 시 화면에 오류 메시지 표시
            cv2.putText(frame, "Tracking failure detected", (100,80), cv2.FONT_HERSHEY_SIMPLEX, 0.75,(0,0,255),2)

        # 프레임 상단에 추적기 유형 표시
        # object tracking 관한 방법 3가지(CSRT, KCF, MOSSE)
        # CSRT : 높은 정확도와 느린 FPS
        cv2.putText(frame, "CSRT" + " Tracker", (100,20), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50),2);
    
        # 디스플레이 상단에 FPS 표시
        # FPS >> 실시간으로 프레임수(Frame Rate) 계산해서 표시
        cv2.putText(frame, "FPS : " + str(int(fps)), (100,50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50), 2);

        # 추적한 객체 화면에 표시
        cv2.imshow("Tracking", frame)

        # ESC 키 누르면 종료
        k = cv2.waitKey(1) & 0xff
        if k == 27 : break
