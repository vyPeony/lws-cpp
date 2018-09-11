r = {}
File.open('dragons') do |file|
  file.each_line do |line|
    id,page,name = line.split(',')
    if r.include?(name)
      if r[name][0] > id
        r[name] = [id,page]
      end
    else
      r[name] = [id,page]
    end
  end
end
r.each do |k,v|
  puts "#{v[0]},#{v[1]},#{k}"
end
