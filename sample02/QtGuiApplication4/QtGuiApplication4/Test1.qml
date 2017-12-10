import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: rect
    width: 300
    height: 300
    color: "blue"
    Column {
        Rectangle{
            color: "transparent"
            width:1
            height: 100
        }

        Button {
            text: "테스트"
            x:100;
            onClicked: {
                //rect.color = D.color.perterriver;
                console.log("테스트 메세지");
//                console.log(scr.pt(999));
                console.log(applicationData.log());
                console.log(applicationData.getCurrentDateTime())
                console.log(scr.log());
//                console.log(scr.pt(1000));
            }
        }
        Rectangle{
            color: "transparent"
            width:1
            height: 20
        }
        Text {
            x:70
            text:"테스트를 위해 작성되었습니다."
        }
    }
}
