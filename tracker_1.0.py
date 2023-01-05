import cv2 # openCV 관련
import sys # sys 모듈은 파이썬 인터프리터가 제공하는 변수와 함수를 직접 제어할 수 있게 해주는 모듈
import paho.mqtt.client as mqtt # mqtt 통신 관련
import json # 이후에 좌표값 json 형식으로 처리하기 위해 선언
import time

# mqtt 연결 관련해 함수 생성
# 4개의 매개변수 (클라이언트, 사용자 데이터, flags, 반환 코드)
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        # 반환 코드  = 0 >> 연결 성공의 의미
        print("connected OK")
    else:
        print("Bad connection Returned code=", rc)
        # 연결되지 않았을 때, 출력되는 각 rc의 의미
        # rc = 1 >> 잘못된 프로토콜 버전으로 연결 거부
        # rc = 2 >> 잘못된 클라이언트 식별자로 연결 거부
        # rc = 3 >> 서버 사용 불가 
        # rc = 4 >> 잘못된 사용자 이름 혹은 비밀번호 
        # rc = 5 >> 승인되지 않음

# mqtt 연결이 안되었을 때
def on_disconnect(client, userdata, flags, rc=0):
    # rc = 0 >> 정상적인 해제, 그 이외의 코드 >> 비정상적인 해제
    print(str(rc))

# on_publish 함수 >> 메시지를 전송완료 했을 때 호출
def on_publish(client, userdata, mid):
    print("In on_pub callback mid= ", mid)

# mqtt관련 기본 세팅
mqttBroker = 'broker.hivemq.com' # 변경하는거 잊지 말기!!!!!!!
client = mqtt.Client() # 클라이언트 객체 생성
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_publish = on_publish

def main():
    client.connect(mqttBroker, 1883) # 여기도 수정하기!!!
    client.loop_start()

    tracker = cv2.TrackerCSRT_create()

    # 비디오 읽어오기
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
        # fps = cv2.getTickFrequency() / ()cv2.getTickCount() - timer);
        fps = (cv2.getTickCount() - timer) / (cv2.getTickFrequency() * 200);

        # 객체 박스 그리기
        if ok:
            # 객체를 측정했을 시 따라 추적하는 내용
            p1 = (int(bbox[0]), int(bbox[1])) # 각각의 센터값을 전송하기 위해
            p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
            cv2.rectangle(frame, p1, p2, (255,0,0), 2, 1)

            cx = str(int(bbox[0] + bbox[2]) // 2)
            cy = str(int(bbox[1] + bbox[3]) // 2)
            #.publish(주제, 페이로드[실제 보내는 메시지], qos[사용할 서비스 품질]  )
            # qos가 0, 1, 2가 아니거나 페이로드 길이가 268435455 바이트보다 크면 에러
            client.publish('carrier0', json.dumps({"x": cx, "y": cy}), 1) # 'carrier0'는 노드레드에 전달할 토픽명!
            print( "x: " + cx + " y: " + cy )
            time.sleep(0.5)
            
        else :
            # 추적실패 메시지   # 제공하는 font 유형 > cv2.FONT_HERSHEY_SIMPLEX
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

    # mqtt 연결 해제
    client.loop_stop()
    client.disconnect()

if __name__ == '__main__' :
    main()
