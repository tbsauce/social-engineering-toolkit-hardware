import storage

# Make the CIRCUITPY drive writable (mount it as read-write)
storage.remount("/", readonly=False)

