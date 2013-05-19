Gem::Specification.new do |s|
  s.name        = 'onyx'
  s.version     = '0.0.0'
  s.date        = '2013-05-19'
  s.summary     = 'A ruby chess engine.'
  s.description = 'A ruby chess engine.'
  s.authors     = ['Ulysse Carion']
  s.email       = 'ulyssecarion@gmail.com'
  s.files       = ["lib/onyx.rb"]
  s.homepage    = 'https://github.com/ulyssecarion/onyx'
  s.files       =  Dir.glob('lib/**/*.rb') + Dir.glob('ext/**/*.{c,h,rb}')
  s.extensions  = ['ext/onyx/extconf.rb']
end