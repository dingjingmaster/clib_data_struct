//
// Created by dingjing on 2021/3/30.
//

#include "folder-model-item.h"
#include <QDateTime>

namespace dingjing
{

const QString& FolderModelItem::displayName() const
{
    return mInfo->displayName();
}

const std::string &dingjing::FolderModelItem::name() const
{
    return mInfo->name();
}

QIcon FolderModelItem::icon() const
{
    const auto i = mInfo->icon();
    return i ? i->qicon() : QIcon{};
}

FolderModelItem::FolderModelItem(const std::shared_ptr<const FileInfo>& info) : mIsCut{false}, mInfo{info}
{
    mThumbnails.reserve(2);
}

FolderModelItem::FolderModelItem(const FolderModelItem& other) : mIsCut{other.mIsCut}, mThumbnails{other.mThumbnails}, mInfo{other.mInfo}
{

}

FolderModelItem::~FolderModelItem()
{

}

QString FolderModelItem::ownerName() const
{
//    QString name;
//    auto user = UserInfoCache::globalInstance()->userFromId(mInfo->uid());
//    if(user) {
//        name = user->name();
//    }
//    return name;
    return "";
}

QString FolderModelItem::ownerGroup() const
{
//    auto group = UserInfoCache::globalInstance()->groupFromId(info->gid());
//    return group ? group->name() : QString();
    return "";
}

const QString &FolderModelItem::displayMtime() const
{
    if(mDispMtime.isEmpty()) {
        if(mInfo->mtime() == 0) {
            mDispMtime = QObject::tr("N/A");
        } else {
            auto mtime = QDateTime::fromMSecsSinceEpoch(mInfo->mtime() * 1000);
            mDispMtime = mtime.toString(Qt::SystemLocaleShortDate);
        }
    }
    return mDispMtime;
}

const QString &FolderModelItem::displayCrtime() const
{
    if(mDispCrtime.isEmpty()) {
        if(mInfo->crtime() == 0) {
            mDispCrtime = QObject::tr("N/A");
        } else {
            auto crtime = QDateTime::fromMSecsSinceEpoch(mInfo->crtime() * 1000);
            mDispCrtime = crtime.toString(Qt::SystemLocaleShortDate);
        }
    }
    return mDispCrtime;
}

const QString &FolderModelItem::displayDtime() const
{
    if(mDispDtime.isEmpty() && mInfo->dtime() > 0) {
        auto mtime = QDateTime::fromMSecsSinceEpoch(mInfo->dtime() * 1000);
        mDispDtime = mtime.toString(Qt::SystemLocaleShortDate);
    }
    return mDispDtime;
}

const QString& FolderModelItem::displaySize() const
{
    if(!mInfo->isDir()) {
        // FIXME: choose IEC or SI units
//        mDispSize = formatFileSize(mInfo->size(), false);
    }
    return mDispSize;
}

// find thumbnail of the specified size
// The returned thumbnail item is temporary and short-lived
// If you need to use the struct later, copy it to your own struct to keep it.
FolderModelItem::Thumbnail* FolderModelItem::findThumbnail(int size)
{
    QVector<Thumbnail>::iterator it;
    for(it = mThumbnails.begin(); it != mThumbnails.end(); ++it) {
        if(it->size == size) { // an image of the same size is found
            return it;
        }
    }
    if(it == mThumbnails.end()) {
        Thumbnail thumbnail;
        thumbnail.status = ThumbnailNotChecked;
        thumbnail.size = size;
        mThumbnails.append(thumbnail);
    }
    return &mThumbnails.back();
}

// remove cached thumbnail of the specified size
void FolderModelItem::removeThumbnail(int size)
{
    QVector<Thumbnail>::iterator it;
    for(it = mThumbnails.begin(); it != mThumbnails.end(); ++it) {
        if(it->size == size) { // an image of the same size is found
            mThumbnails.erase(it);
            break;
        }
    }
}

}

