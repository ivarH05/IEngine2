#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <utility>

namespace IEngine
{
	template<typename... Args>
	class Event
	{
	public:
		using ListenerID = size_t;
		using Listener = std::function<void(Args...)>;

		class Connection
		{
		public:
			Connection() = default;

			Connection(const Connection&) = delete;
			Connection& operator=(const Connection&) = delete;

			Connection(Connection&& other) noexcept
				: _event(other._event), _id(other._id)
			{
				other._event = nullptr;
			}

			Connection& operator=(Connection&& other) noexcept
			{
				if (this != &other)
				{
					Disconnect();
					_event = other._event;
					_id = other._id;
					other._event = nullptr;
				}
				return *this;
			}

			~Connection()
			{
				Disconnect();
			}

			void Disconnect()
			{
				if (_event != nullptr)
				{
					_event->RemoveListener(_id);
					_event = nullptr;
				}
			}

			void Clear()
			{
				listeners.clear();
			}

			explicit operator bool() const
			{
				return _event != nullptr;
			}

		private:
			friend class Event;

			Connection(Event* event, ListenerID id)
				: _event(event), _id(id)
			{}

			Event* _event = nullptr;
			ListenerID _id = 0;
		};

		ListenerID AddListener(const Listener& listener)
		{
			return AddListener(listener, false);
		}

		Connection Connect(Listener listener)
		{
			return Connection(this, AddListener(std::move(listener), false));
		}

		Connection ConnectOnce(Listener listener)
		{
			return Connection(this, AddListener(std::move(listener), true));
		}

		void RemoveListener(ListenerID id)
		{
			listeners.erase(id);
		}

		void Invoke(Args... args)
		{
			std::vector<ListenerID> listenerIDs;
			listenerIDs.reserve(listeners.size());
			for (const auto& [id, listener] : listeners)
				listenerIDs.push_back(id);

			for (ListenerID id : listenerIDs)
			{
				auto it = listeners.find(id);
				if (it == listeners.end())
					continue;

				try
				{
					if (it->second.once)
					{
						Listener listener = std::move(it->second.listener);
						listeners.erase(it);
						listener(args...);
					}
					else
					{
						it->second.listener(args...);
					}
				}
				catch (const std::exception& e)
				{
					// Handle the exception (e.g., log it)
					std::cerr << "Exception in event listener: " << e.what() << std::endl;
				}
				catch (...)
				{
					// Handle unknown exceptions
					std::cerr << "Unknown exception in event listener." << std::endl;
				}
			}
		}

	private:
		struct ListenerEntry
		{
			Listener listener;
			bool once;
		};

		ListenerID AddListener(Listener listener, bool once)
		{
			ListenerID id = nextListenerID++;
			listeners.emplace(id, ListenerEntry{ std::move(listener), once });
			return id;
		}

		std::unordered_map<ListenerID, ListenerEntry> listeners;
		ListenerID nextListenerID = 0;
	};
}