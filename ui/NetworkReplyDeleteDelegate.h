#ifndef NETWORKREPLYDELETEDELEGATE_H
#define NETWORKREPLYDELETEDELEGATE_H

class NetworkReplyDeleteDelegate
{
public:
    template<typename T>
    void operator()(T *data) const
    {
        if(data) data->deleteLater();
    }
};


#endif // NETWORKREPLYDELETEDELEGATE_H
