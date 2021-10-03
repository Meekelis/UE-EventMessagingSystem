Event Messaging System
=====================
![Event Messaging System Introduction Header Image](https://i.imgur.com/FiNtGH2.png)

Event Messaging System is a plugin for Unreal Engine 4.26. It allows C++ and Blueprint actors to call events on each other without having soft or hard reference links, but instead by using actor tags and class filters. All events are called in a static way from anywhere in C++ or Blueprints.

Event messages can have payloads with various data types in key - value pairs.

The code is very well documented, you should be able to use it and extend is as you wish.

## Example uses of this system

1. In a story-driven single player game, the player enters a new beautiful area. A multicast event "OnEnterBeautifulArea" is sent to all characters that implement a behavior for this event. Some characters play voiceover lines to remark about this area.
2. A player dies and a multicast event "OnPlayerDead" is sent to all game systems that have implemented a behavior for it.
3. In an architectural demo, a light switch is flipped, and it sends "TurnLightsOn" event to all blueprints of lights.

## Tutorial playlist

Please click or tap the video below for a 5-part tutorial playlist.

[![YouTube Tutorial Playlist for Event Messaging System](https://i.imgur.com/UPlSDAs.png)](https://www.youtube.com/watch?v=T3-4kFnf9PQ&list=PLV0y8WUdGIPTVUo_nJWoO6i64tUhKT8vn&index=1)

## Download
See the [release page](https://github.com/Meekelis/UE-EventMessagingSystem/releases/) to download production-ready versions of this plugin: https://github.com/Meekelis/UE-EventMessagingSystem/releases/.
